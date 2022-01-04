//implemenation of the HSS class

#include "HSS.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>


//used to create a unique key for each word in the dictionary
std::string reverse(std::string word)
{
	int num = word.length();
	std::string temp;
	for(int i = num - 1; i >= 0; i--)
	{
		temp.push_back(word[i]);
	}
	return temp;		
}

//searches a users misspelled word and counts how many like characters are in the given dictionary word
int stringSearcher(std::string input, std::string dictWord)
{
	int count = 0;				
	
	if(input.length() > dictWord.length())
	{
		return -1;
	}		

	for(int i = 0; i < dictWord.length(); i++)
	{
		if(dictWord.find(input[i]) != std::string::npos)
		{
			count++;
		}		
	}
	return count;
}



//default constructor
HSS::HSS(void)
: buckets_(0),
	hTable_(nullptr)
{}


//init constructor
HSS::HSS(int b)
: buckets_(b),
	hTable_(new Node * [b])
{
	//set each node in the hashtable to a nullptr
	for(int i = 0; i < b; i++)
	{
		this->hTable_[i] = nullptr;
	}
}

size_t HSS::size()
{
	return this->buckets_;
}


//adds the words from the dictionary file to the hash table	
void HSS::addWords(std::string filename)
{
	//initialize input stream from the passed in filename
	std::string line;
	std::ifstream dictFile;
	dictFile.open(filename);
	//if the file opens properly, get each line
	if(dictFile.is_open())
	{
		while(getline(dictFile, line))
		{
			//while there is a line to get
			//hash word to table
			std::string temp = reverse(line);
			this->addToHashTable(temp, line);
		}
		//close the file once the passed in file runs out of words
		dictFile.close();
	}
	else
	{
		//if the file does not open, print to console
		std::cout << "Unable to open the file..." << std::endl;
	}		
}


//adds a word to the hash table
void HSS::addToHashTable(std::string key, std::string value)
{
	//index will represent the returned hash value for the passed in value
	int index = this->hasher(key);	
	//current is used as a starting value for insertion
	Node * current = this->hTable_[index];

	//if the current value is a nullptr, then no words have been hashed to this index yet
	//create a new node and add it to the hash table at the generated index		
	if(current == nullptr)
	{
		Node * entry = new Node(key, value);
		this->hTable_[index] = entry;
	}
	//else if it is not empty, create a new node and set its next property to the value of current
	//then update the hash table index value to the new node, effectively adding the key/value as the new head of the linked list
	//create a new node and initialize it with the passed in key and value 
	else
	{
		Node * newNode = new Node(key, value);
		//set the next property to point to the 
		newNode->setNext(this->hTable_[index]);
		//updates the head of the linked list at this value
		this->hTable_[index] = newNode;
	}	
}


//hash function for a string
int HSS::hasher(std::string key)
{
	//range based for loop that adds the character to the hash value provided 
	int character;
	size_t hash = 501;
	for(auto x: key)
	{
		character = x;
		hash = hash + character;
	}	
	//returns the hash value after looping modulo the size of the hash table	
	return (hash % this->buckets_);
}



//returns the word if it is found in the hash table, if not returns not found

std::string HSS::getWord(std::string key)
{
	//initialize index as the hashed value for the passed in key
	size_t index = this->hasher(key);
	//initialize current with the head of the linked list at the hash value
	Node * current = this->hTable_[index];

	//while current is not a nullptr
	while(current)
	{
		//if currents key matches the searched for key, return its value
		if(current->getKey() == key)
		{
			return current->getValue();
		}
		//reinitialize current with its next pointer, if it is a null the next while loop iteration will terminate
		current = current->getNext();
		
		
	}
	//if the searched for word is not found, return not found
	return "not found";
}


Node * HSS::findCloseWords(std::string key)
{
	//initialize a new node pointer to represent the head of a linked list that will be returned
	Node * list = new Node(reverse(key), key);
	//current will represent the current linked list node being examined
	Node * current;
	//firstTwo is used to store the first two characters of the passed in key to use in comparisons as the hash table is searched through
	std::string firstTwo;
	firstTwo.push_back(key[0]);
	firstTwo.push_back(key[1]);

	//loop through each index in the hash table
	for(int i = 0; i < this->buckets_; i++)
	{
		//at each iteration of the loop, the current node is set to i's value so that each index is searched through
		if(current = this->hTable_[i]);
		{
			//while current is not a nullptr, examine each node in its chain and see if the first two characters match the firstTwo string
			while(current)	
			{
				if(current->getValue() != key)
				{
					//if the first two characters match, add it to the list and set list to its next property to continue to add as more words are found
					if(current->getValue()[0] == firstTwo[0] && current->getValue()[1] == firstTwo[1])
					{	
						Node * add = new Node(current->getKey(), current->getValue());	
						add->setNext(list);
						list = add;
					}
				}
				//current gets set to its next property to continue to search through the current chain		
				current = current->getNext();
			}
		}
	}
	//at this point, the whole hashtable has been examined and the linked list is returned
	return list;
}

//checks if the word the user inputs is in the dictionary, if it exists, prints "true" and a list with all the words in the dictionary starting
//with the first two letters, if the word does not exist and has not resemblance of any other word in the dictionary return false
bool HSS::finder(std::string input)
{
	//if the word exists in the dictionary, create a list of all the words that start with the first two letters as the users input
	if(this->getWord(reverse(input)) == input)
	{
		Node * list = this->findCloseWords(input);
		std::cout << std::endl;
		std::cout << "True" << std::endl;
		//loop through the list of words and print them out one after another and return true
		while(list)
		{
			if(list->getValue() != input)
			{
				std::cout << std::endl;
				std::cout << list->getValue() << std::endl;
			}
			list = list->getNext();	
		}
		return true;
	}
	return false;
}


//creates a list of words that start with the first letter of the users misspelled word
Node * HSS::firstLetterMatches(std::string input)
{
	Node * current;
	Node * list = new Node();
	//loop through the hash table and add all words that have the first letter matching as the users misspelled word	
	for(int i = 0; i < this->buckets_; i++)
	{
		//if the current node is not a nullptr, loop through its chain to search for words that match the first letter
		if(current = this->hTable_[i])
		{
			while(current)
			{
				//if the current words first letter matches the first letter of the users inputted word, add it to the linked list
				if(current->getValue()[0] == input[0])
				{
					Node * add = new Node(current->getKey(), current->getValue());
					add->setNext(list);
					list = add;
				}
				current = current->getNext();
			}
		}
	}
	//return the list of words that have the same first letter as the users misspelled word
	return list;
}

//creates a smaller list of suggestable words for recommending 
Node * HSS::narrowChoices(std::string input)
{
	//loop through the list created from the firstLetter matches
	Node * list = this->firstLetterMatches(input);
	Node * newList = new Node();	
	while(list)
	{
		//if the users attempted word has all the matching characters as the dictionary word, or it is one less in length as
		//the dictionary word, add it to the list
		if(stringSearcher(input, list->getValue()) == list->getValue().length() ||  list->getValue().length()  -1 == input.length())
		{
			Node * add = new Node(list->getKey(), list->getValue());
			add->setNext(newList);
			newList = add;
		}
		list = list->getNext();
	}	
	//returns a new list of suggestable words
	return newList;
}

//does the recommending 
std::string HSS::recommender(std::string input)
{
	Node * list = this->narrowChoices(input);
	//loop through the list created from narrowChoices
	while(list)
	{
		//if the number of matching characters is more than half plus one of the dictionary word and the dictionary word
		//is greater than or equal to the users input words length, it is suggestable and return this word
		if(stringSearcher(input,list->getValue()) > list->getValue().length() / 2 + 1 && list->getValue().length() >= input.length())
		{
			std::string word = list->getValue();
			return word;
		}
		//else if stringSearcher returns -1, that means the users word is not close enough to any dictionary word, so return "not found"
		else if(stringSearcher(input, list->getValue()) == -1)
		{
			return "not found";
		}
		list = list->getNext();
	}
}























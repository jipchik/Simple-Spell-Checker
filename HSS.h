//declaration of the class that will do the hashing function and operations; HSS->Hash Slinging Slasher

#ifndef _HSS_H_
#define _HSS_H_

#include "Node.h"
#include <string>

class HSS
{
	public:

	int buckets_;
	Node ** hTable_;
		

	public:

	//default constructor
	HSS();
	//initializing constructor, sets the number of buckets and creates a table of buckets
	HSS(int b);
	//returns the size of the hash table
	size_t size(void);
	//adds the words from the file to the table via hash function
 	void addWords(std::string filename);
	//uses the word passed in for the hash value creation
	int hasher(std::string key);
	//adds a word to the hash table
	void addToHashTable(std::string key, std::string value);
	//gets the the requested value
	std::string getWord(std::string key);
	//returns a linked list of words that have the same first two letters
	Node * findCloseWords(std::string key);
	//returns true with the list of words that are similar to the user input, false if no resemblance
	bool finder(std::string input);	
	//recommends a word from the dictionary if the user has misspelled the word
	std::string recommender(std::string input);
	//returns a linked list of all the closest matches found from the users misspelled word
	Node * narrowChoices(std::string input);
	//returns a linked list of all words that start with the same first letter as the users misspelled word
	Node * firstLetterMatches(std::string input);
};



#endif

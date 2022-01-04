//testing spell checker here

#include "HSS.h"
#include "TimeInterval.h"
#include <iostream>
#include <string>



int main(void)
{
	//instantiate a new time interval object
	TimeInterval t;
	
 	bool keepGoing = true;

	//controls the program
	while(keepGoing)
	{	
	//creates a hash table with 51 buckets
		HSS * ht = new HSS(51);
		//adds the words to the hash table
		ht->addWords("Dictionary.txt");
		std::string input;
		std::cout << std::endl;	
		std::cout << "Provide me a word and we will see if it is in the dictionary: " << std::endl;
		std::cin >> input;	
		std::cout << std::endl;	

		t.start();
		bool result = ht->finder(input);
		t.stop();
		//if the provided word is found, prints a list of words and then prints the execution time
		if(result)
		{
			std::cout << std::endl;
			std::cout << t.GetInterval()  << "  micro-seconds" << std::endl;	
			std::cout << std::endl;
		}
		//if the word is not found, it searches for a similar word and asks the user if that is the word they want
		else if(!result)
		{
			std::string r =	ht->recommender(input);
			if(r == "not found")
			{
				std::cout << "False" << std::endl;	
			}
			else if (r != "not found")
			{
				std::string rec = "Do you mean ";
				std::string qMark = "?";
				std::string phrase = rec + r + qMark;
				std::string res;
				std::cout << phrase << std::endl;
				std::cout << "'Y' to accept recommendation. 'N' to decline recommendation.";
				std::cout << std::endl;
				std::cin >> res;
				if(res.front() == 'y' || res.front() == 'Y')
				{	
					t.start();
					ht->finder(r);
					t.stop();
					std::cout << std::endl;
					std::cout << t.GetInterval() << " micro-seconds" <<  std::endl;					
					std::cout << std::endl;
				}
				//if no word is found that resembles any dictionary words, print false
				else
				{
					std::cout << "False" << std::endl;		
				}
			}
		}	
		//ask the user if they want to continue the program or exit
		std::cout << std::endl;
		std::cout << "Would you like to continue?" << std::endl;
		std::cout << "'Y' to continue. 'N' to quit.";
		std::cout << std::endl;
		std::cin >> input;
		if(input.front() == 'N' || input.front() == 'n')
		{
			keepGoing = false;
		}		
	}
}

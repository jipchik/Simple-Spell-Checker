//declaration of a node in a hash table that will represent a singly linked list
#ifndef _NODE_H_
#define _NODE_H_

#include <string>


class Node
{
	private: 

	std::string value_;
	std::string key_;
	Node * next_;
	
	public:
	
	//default constructor
	Node();
	//init constructor
	Node(std::string key, std::string val);
	//getter for the value
	std::string getValue();
	//setter for the value
	void setValue(std::string newVal);
	//getter for the next node
	Node * getNext();
	//sets the next node
	void setNext(Node * next);
	//gets the key for a specific node
	std::string getKey();
	//sets the key for a specific node
	void setKey(std::string k);	
};


#endif

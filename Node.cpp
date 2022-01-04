//implementation of a node class for a singly linked list

#include "Node.h"


Node::Node(void)
:	value_(""),
	key_(""),
	next_(nullptr)
{}


Node::Node(std::string  key, std::string value)
:	value_(value),
	key_(key),
	next_(nullptr)
{}

void Node::setNext(Node * n)
{
	this->next_ = n;
}

Node * Node::getNext(void)
{
	return this->next_;
}

void Node::setKey(std::string k)
{
	this->key_ = k;
}

std::string Node::getKey(void)
{
	return this->key_;
}

void Node::setValue(std::string val)
{
	this->value_ = val;
}

std::string Node::getValue(void)
{
	return this->value_;
}


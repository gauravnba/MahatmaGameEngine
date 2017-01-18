#include "pch.h"

#include "SList.h"

using namespace MahatmaGameEngine;
using namespace std;

SList::SList() :
	listFront(nullptr), listBack(nullptr), listSize(0)
{
}

SList::SList(const SList &listObject) :
	listFront(nullptr), listBack(nullptr), listSize(0)
{
	listSize	= listObject.listSize;

	Node* tempNode	= listObject.listFront;
	for (int i = 0; i < listSize; i++)
	{
		pushBack(tempNode->item);
		tempNode = tempNode->next;
	}
}

SList& SList::operator=(const SList &listObject)
{
	listSize = listObject.listSize;
	
	Node* tempNode = listObject.listFront;
	for (int i = 0; i < listSize; i++)
	{
		pushBack(tempNode->item);
		tempNode = tempNode->next;
	}
	return *this;
}

SList::~SList()
{
	// Clear the list from front to back.
	for( int i = 0; i < listSize; i++)
	{
		Node* tempNode	= new Node;
		tempNode		= listFront;
		listFront		= tempNode->next;
		delete tempNode;
	}
}

void SList::pushFront(int32_t data)
{
	Node* tempNode	= new Node;
	tempNode->item	= data;
	tempNode->next	= listFront;
	listFront		= tempNode;

	listSize		+= 1;
}

int32_t SList::popFront()
{
	Node* tempNode		= new Node;
	tempNode			= listFront;
	int32_t returnItem	= tempNode->item;

	listFront		= tempNode->next;
	delete tempNode;

	listSize		-= 1;

	return returnItem;
}

void SList::pushBack(int32_t data)
{
	Node* tempNode	= new Node;
	tempNode->item	= data;
	tempNode->next	= listBack;
	listBack		= tempNode;

	listSize		+= 1;
}

void SList::clear()
{
	//Remove all nodes from front to back.
	for (int i = 0; i < listSize; i++)
	{
		Node* tempNode	= new Node;
		tempNode		= listFront;
		listFront		= tempNode->next;
		delete tempNode;
	}

	//Reset the member variables.
	listFront	= nullptr;
	listBack	= nullptr;
	listSize	= 0;
}

int32_t SList::size() const
{
	return listSize;
}

bool SList::isEmpty() const
{
	if (listSize == 0)
	{
		return true;
	}

	return false;
}

int32_t SList::front()
{
	int32_t frontItem = listFront->item;
	return frontItem;
}

int32_t SList::back()
{
	int32_t backItem = listBack->item;
	return backItem;
}

const int32_t& SList::front() const
{
	return (const int32_t)(listFront->item);
}

const int32_t& SList::back() const
{
	return (const int32_t)(listBack->item);
}
#include "pch.h"

#include "SList.h"

using namespace MahatmaGameEngine;
using namespace std;

template <typename T>
SList<T>::SList() :
	mFront(nullptr), mBack(nullptr), mSize(0)
{
}

template <typename T>
SList<T>::SList(const SList<T> &obj) :
	mFront(nullptr), mBack(nullptr), mSize(0)
{
	mSize	= obj.mSize;

	Node* temp	= obj.mFront;
	while(temp != nullptr)
	{
		pushBack(temp->item);
		temp = temp->next;
	}
}

template <typename T>
SList& SList::operator=(const SList &obj)
{
	if (this != &obj)
	{
		clear();

		//Deep copy
		Node* temp = obj.mFront;
		while (temp != nullptr)
		{
			pushBack(temp->item);
			temp = temp->next;
		}
	}
	return *this;
}

template <typename T>
SList::~SList()
{
	// Clear the list from front to back.
	for (int i = 0; i < mSize; i++)
	{
		Node* temp	= new Node;
		temp		= mFront;
		mFront			= temp->next;
		delete temp;
	}
}

template <typename T>
void SList::pushFront(int32_t data)
{
	Node* tempNode	= new Node;
	tempNode->item	= data;
	tempNode->next	= mFront;
	mFront		= tempNode;

	mSize		+= 1;
}

template <typename T>
int32_t SList::popFront()
{
	Node* tempNode		= new Node;
	tempNode			= mFront;
	int32_t returnItem	= tempNode->item;

	mFront		= tempNode->next;
	delete tempNode;

	mSize		-= 1;

	return returnItem;
}

template <typename T>
void SList::pushBack(int32_t data)
{
	Node* tempNode	= new Node;
	tempNode->item	= data;
	tempNode->next	= mBack;
	mBack		= tempNode;

	mSize		+= 1;
}

template <typename T>
void SList::clear()
{
	//Remove all nodes from front to back.
	for (int i = 0; i < mSize; i++)
	{
		Node* tempNode	= new Node;
		tempNode		= mFront;
		mFront		= tempNode->next;
		delete tempNode;
	}

	//Reset the member variables.
	mFront	= nullptr;
	mBack	= nullptr;
	mSize	= 0;
}

template <typename T>
int32_t SList::size() const
{
	return mSize;
}

template <typename T>
bool SList::isEmpty() const
{
	if (mSize == 0)
	{
		return true;
	}

	return false;
}

template <typename T>
int32_t SList::front()
{
	int32_t frontItem = mFront->item;
	return frontItem;
}

template <typename T>
int32_t SList::back()
{
	int32_t backItem = mBack->item;
	return backItem;
}

template <typename T>
const int32_t& SList::front() const
{
	return (const int32_t)(mFront->item);
}

template <typename T>
const int32_t& SList::back() const
{
	return (const int32_t)(mBack->item);
}
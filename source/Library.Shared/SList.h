#pragma once

#include <cstdint>
#include <exception>

namespace MahatmaGameEngine
{
	//*SList Class
	/**
	* This a templated singly linked list class present in the 'MahatmaGameEngine' namespace.
	*/
	template <typename T>
	class SList
	{
	public:
		/** 
		* The default constructor to generate the SList. 
		* It generates an SList instance with nullptr front and back nodes.
		*/
		SList();

		/**
		* Copy constructor of the class.
		*/
		SList(const SList& obj);

		/**
		* Assignment operator method for SList
		*/
		SList& operator= (const SList& obj);

		/** 
		* The destructor of the SList.
		*/
		~SList();

		/** 
		* Push new item into the front of the list.
		* @param data The data to be put into the node of the list.
		*/
		void pushFront(T data);

		/**
		* Pop the front item from the list and return the item value.
		*/
		T popFront();

		/**
		* Push new item into the back of the list.
		* @param data The data to be put into the node of the list.
		*/
		void pushBack(T data);

		/**
		* Remove all the items from the list and resets it.
		*/
		void clear();

		/**
		* Returns true if there are no items in the list.
		*/
		bool isEmpty() const;

		/**
		* Returns the item in the front node of the list.
		*/
		T& front();

		/**
		* Returns the item in the back node of the list.
		*/
		T& back();

		/**
		* Returns a const reference to the item in the front node of the list.
		*/
		const T& front() const;

		/**
		* Returns a const reference to the item in the back node of the list.
		*/
		const T& back() const;

		/**
		* Returns the current number of items in the list.
		*/
		std::uint32_t size() const;

	private:
		std::uint32_t mSize;		/**< Current number of Node elements in the class.*/

		/**
		* Private struct Node holds the data of a node and the pointer to the next node.
		*/
		struct Node
		{
			T item;				/**< Used to store the data item as defined by the user.*/
			Node* next = nullptr;			/**< Pointer to the next node in the list.*/
		};

		Node* mFront;			/**< Pointer to the first Node in the SList.*/
		Node* mBack;			/**< Pointer to the last Node in the SList.*/
	};
}

#include "SList.inl"
#pragma once

namespace MahatmaGameEngine
{
	//*SList Class
	/**
	* This a templated singly linked list class present in the 'MahatmaGameEngine' namespace.
	*/
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
		SList(const SList &listObject);

		/**
		* Assignment operator method for SList
		*/
		SList& operator= (const SList& listObject);

		/** 
		* The destructor of the SList.
		*/
		~SList();

		/** 
		* Push new item into the front of the list.
		* @param data The data to be put into the node of the list.
		*/
		void pushFront(std::int32_t data);

		/**
		* Pop the front item from the list and return the item value.
		*/
		std::int32_t popFront();

		/**
		* Push new item into the back of the list.
		* @param data The data to be put into the node of the list.
		*/
		void pushBack(std::int32_t data);

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
		std::int32_t front();

		/**
		* Returns the item in the back node of the list.
		*/
		std::int32_t back();

		/**
		* Returns a const reference to the item in the front node of the list.
		*/
		const std::int32_t& front() const;

		/**
		* Returns a const reference to the item in the back node of the list.
		*/
		const std::int32_t& back() const;

		/**
		* Returns the current number of items in the list.
		*/
		std::int32_t size() const;

	private:
		std::int32_t listSize;		/**< Current number of Node elements in the class.*/

		struct Node
		{
			std::int32_t item;
			Node* next;
		};

		Node* listFront;			/**< Pointer to the first Node in the SList.*/
		Node* listBack;				/**< Pointer to the last Node in the SList.*/
	};
}
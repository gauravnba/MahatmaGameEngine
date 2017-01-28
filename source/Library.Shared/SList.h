#pragma once

#include <cstdint>
#include <exception>

namespace MahatmaGameEngine
{
	//*SList Class
	/**
	* This is a templated singly linked list class present in the 'MahatmaGameEngine' namespace.
	*/
	template <typename T>
	class SList
	{
	private:
		/**
		* Private struct Node holds the data of a node and the pointer to the next node.
		*/
		struct Node
		{
			T item;							/**< Used to store the data item as defined by the user.*/
			Node* next = nullptr;			/**< Pointer to the next node in the list.*/
		};

	public:
		/**
		* The iterator class created to traverse the SList.
		*/
		class Iterator
		{
			friend class SList<T>;
		public:
			/**
			* Default constructor for embedded class Iterator.
			* Initializes the current node and current list of the iterator to null.
			*/
			Iterator();

			/**
			* Copy constructor that deep copies the properties of the Iterator 'obj' object to this object.
			*/
			Iterator(const Iterator& obj);

			/**
			* Default Destructor for Iterator
			*/
			~Iterator();

			/**
			* Assignment operator that assigns the parameter obj (Iterator object) to this object.
			* @param Iterator is input as the right hand side.
			*/
			Iterator& operator=(const Iterator& obj);

			/**
			* Equality operator returns true if parameter obj (Iterator object) is equivalent to this object.
			* @param Iterator is input as the right hand side.
			*/
			bool operator==(const Iterator& obj) const;

			/**
			* Inequality operator returns true if parameter obj (Iterator object) is not equivalent to this object.
			* @param Iterator is input as the right hand side.
			*/
			bool operator!=(const Iterator& obj) const;

			/**
			* Post-increment operator increments the position of the iterator to the next Node in
			the list and returns that node, if not at the end.
			*/
			Iterator& operator++();

			/**
			* Pre-increment operator increments the position of the iterator to the next Node and
			returns the previous position, if not at the end.
			*/
			Iterator operator++(int temp);

			/**
			* Dereference operator returns the item of the node the iterator is currently pointing to.
			*/
			T& operator*() const;

		private:
			/**
			* Constructor that accepts two arguments for the corresponding member variables of Iterator.
			* Is private because it is only used by the SList class in certain methods.
			*/
			Iterator(Node* node, SList<T>* list);
			Node*	  mCurrentNode;				/**< The node the iterator is currently pointing to.*/
			SList<T>* mCurrentList;				/**< The list the iterator is currently associated to.*/
		};

		/** 
		* The default constructor to generate the SList. 
		* It generates an SList instance with nullptr front and back nodes.
		*/
		SList();

		/**
		* Copy constructor of the class.
		* @param the list to be copied from
		*/
		SList(const SList& obj);

		/**
		* Assignment operator method for SList
		* @param the list to be copied from
		*/
		SList& operator=(const SList& obj);

		/** 
		* The destructor of the SList.
		*/
		~SList();

		/**
		* Push new item into the front of the list.
		* @param data The data to be put into the node of the list.
		*/
		Iterator pushFront(T data);

		/**
		* Pop the front item from the list and return the item value.
		*/
		T popFront();

		/**
		* Push new item into the back of the list.
		* @param data The data to be put into the node of the list.
		*/
		Iterator pushBack(T data);

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

		/**
		* Returns Iterator that points to the front of the SList.
		*/
		Iterator		begin();

		/**
		* Returns an iterator that points to the node next to the back.
		*/
		Iterator		end();

		/**
		* Inserts item into the list after the input argument it (type iterator)
		* @param it - the operator to be inserted after.
		* @param data - the data to be inserted.
		*/
		Iterator		insertAfter(const Iterator& it, T data);

		/**
		* Returns iterator to the first node encountered with the given value stored in it.
		* @param value - the value to find the iterator with
		*/
		Iterator		find(const T& value);

		/**
		* Removes the first node encountered with the given data in it.
		* @param value - the value to find and remove the iterator with.
		*/
		void			remove(const T& value);

	private:
		std::uint32_t mSize;	/**< Current number of Node elements in the class.*/
		Node* mFront;			/**< Pointer to the first Node in the SList.*/
		Node* mBack;			/**< Pointer to the last Node in the SList.*/
	};
}

#include "SListIterator.inl"
#include "SList.inl"
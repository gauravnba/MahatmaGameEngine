#pragma once

#include <cstdint>
#include <exception>
#include <memory>

namespace MahatmaGameEngine
{
	//*SList Class
	/**
	* This is a templated singly linked list class present in the 'MahatmaGameEngine' namespace.
	*/
	template <typename T>
	class Vector
	{
	public:
		class Iterator
		{
			friend class Vector<T>;

		public:
			/**
			* Default constructor for embedded class Iterator. Initializes the member variables and array.
			*/
			Iterator();

			/**
			* Copy constructor that deep copies the properties of the Iterator 'obj' object to this object.
			* @param existing iterator to copy from.
			*/
			Iterator(const Iterator& obj);

			/**
			* Default Destructor for Iterator.
			*/
			~Iterator();

			/**
			* Assignment operator that assigns the parameter obj (Iterator object) to this object.
			* @param Iterator is input as the right hand side.
			* @return Returns the new values of the iterator as a reference.
			* @exception thrown if the iterator on the left hand side belongs to a different vector
			than the one on the right hand side.
			*/
			Iterator& operator=(const Iterator& obj);

			/**
			* Equality operator returns true if parameter obj (Iterator object) is equivalent to this object.
			* @param Iterator is input as the right hand side.
			* @return Boolean true if equality passed, false otherwise.
			*/
			bool operator==(const Iterator& obj) const;

			/**
			* Inequality operator returns true if parameter obj (Iterator object) is not equivalent to this object.
			* @param Iterator is input as the right hand side.
			* @return Boolean true if inequality passed, false otherwise.
			*/
			bool operator!=(const Iterator& obj) const;

			/**
			* Pre-increment operator increments the position of the iterator to the next item in
			the list and returns that node, if not at the end.
			* @return new value of the iterator as reference.
			* @exception thrown if iterator is already at the end of the vector.
			*/
			Iterator& operator++();

			/**
			* Post-increment operator increments the position of the iterator to the next item and
			returns the previous position, if not at the end.
			* @return copy of the previous value of the iterator.
			* @exception thrown if iterator is already at the end of the vector.
			*/
			Iterator operator++(int);

			/**
			* Dereference operator returns the item of the node the iterator is currently pointing to.
			* @return 
			*/
			T& operator*() const;

		private:
			/**
			* Constructor to create custom iterators by the Vector class.
			* @param index to which the iterator points to.
			* @param vector to which the iterator belongs to.
			*/
			Iterator(std::uint32_t index, Vector<T>* vector);

			std::uint32_t mIndex;					/**< the index in the vector the iterator is pointing to. */
			const Vector<T>* mVector;				/**< the identity of the vector the iterator belongs to.  */
		};

		/**
		* Default constructor initializes the vector to be empty.
		*/
		Vector();

		/**
		* Copy Constructor deep copies the vector pass as argument
		* @param obj - the vector to deep copy from.
		*/
		Vector(const Vector& obj);

		/**
		* Default destructor defined because 
		*/
		~Vector();

		/**
		* Reserves new capacity for the vector to store more elements into.
		* @param the total amount of capacity of data to reserve.
		* @exception - thrown if the capacity to reserve is less than the existing size of the vector.
		*/
		void reserve(std::uint32_t capacity);

		/**
		* Assignment operator that deep copies the right hand side of 
		the operator to the Vector on the right hand side.
		* @param the vector to deep copy from.
		* @return address of the deep copied vector.
		*/
		Vector<T>& operator=(const Vector<T>& obj);

		/**
		* At([]) operator to access elements at a particular index in vector.
		* @param It is the reference to the iterator that we need to access.
		* @return returns the address of the element at index.
		* @exception thrown when the index passed is out of bounds.
		*/
		T& operator[](std::uint32_t index);

		/**
		* The const method for the At([]) operator.
		* @param It is the reference to the iterator that we need to access.
		* @return returns the address of the element at index.
		* @exception thrown when the index passed is out of bounds.
		*/
		const T& operator[](std::uint32_t index) const;

		/**
		* Returns iterator to the first element in the vector.
		* @return copy of the iterator at begin.
		*/
		Iterator begin() const;

		/**
		* Returns iterator to the element one after the last element.
		* @return copy of the iterator at end.
		*/
		Iterator end() const;

		/**
		* To access the size of the vector.
		* @return copy of unsigned integer.
		*/
		std::uint32_t size();

		/**
		* To get the current maximum capacity of the vector.
		* @return copy of unsigned integer.
		*/
		std::uint32_t capacity();

		/**
		* Returns whether the vector empty or not.
		* @return boolean value is true if vector is empty.
		*/
		bool isEmpty();

		/**
		* Pushes data into the end of the vector.
		* @param data to push to the vector
		* @return the iterator to the data that was just pushed.
		*/
		Iterator pushBack(const T& data);

		/**
		* Removes the last item from the vector and returns it to the caller.
		* @return returns a copy of the last item on the vector.
		*/
		T popBack();

		/**
		* Gives the first element in the vector.
		* @return the address of the first element in the vector.
		* @exception thrown if there are no items in the vector.
		*/
		T& front();

		/**
		* Const version of front() for const vector. Gives the first element in the vector.
		* @return the address of the first element in the vector.
		* @exception thrown if there are no items in the vector.
		*/
		const T& front() const;

		/**
		* Returns the element at the back of the vector.
		* @return the address of the last element in the vector.
		* @exception thrown if there are no items in the vector.
		*/
		T& back();

		/**
		* Const version of the back method for const lists. Gives the first element in the vector.
		* @return the address of the last element in the vector.
		* @exception thrown if there are no items in the vector.
		*/
		const T& back() const;

		/**
		* The method cleans the whole vector out and initializes it to its default constructed form.
		*/
		void clear();

		/**
		* Finds a value in the vector and returns an iterator to it. If not found, returns end().
		* @param const reference of item is the value to search for in the vector.
		* @return returns a copy of an Iterator pointing to given item.
		*/
		Iterator find(const T& item) const;

		/**
		* Finds a value in the vector and removes it. Do nothing if not found.
		* @param item is the value to seek and remove.
		*/
		void remove(const T& item);

	private:
		std::uint32_t mSize;						/**< The current number of elements in the vector. */
		std::uint32_t mCapacity;					/**< The maximum number of elements the vector can store before a call to reserve.*/
		const std::uint32_t mIncreaseBy = 4;		/**< The default number of spaces in memory that will be added to the capacity when mSize==mCapacity*/
		T* mArray;									/**< Pointer to the array that the vector stores its elements in.*/
	};
}

#include "Vector.inl"
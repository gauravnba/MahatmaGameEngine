#pragma once

#include <cstdint>
#include <exception>
#include <cstring>
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"

namespace MahatmaGameEngine
{
	/**
	* Templated HashMap class uses a key, value pair of any type with a default hash function. 
	* A user-defined hash function can be passed by using the third type argument of hash function.
	*/
	template <typename TKey, typename TData, typename HashFunction = DefaultHash<TKey>, typename ComparisonFunctor = DefaultCompare<TKey>>
	class HashMap final
	{
	public:
		//TypeDefs specific to the HashMap class
		typedef std::pair<TKey, TData> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;

		/**
		* Iterator class of HashMap.
		*/
		class Iterator
		{
			friend class HashMap;
		public:
			/**
			* Constructor of the Iterator class to the HashMap, initializes the Vector pointer and Index.
			*/
			Iterator();

			/**
			* Copy constructor of Iterator to HashMap.
			* @param obj is the Iterator on the right hand side to copy from.
			*/
			Iterator(const Iterator& obj);

			/**
			* Default destructor of the Iterator to HashMap
			*/
			~Iterator() = default;

			/**
			* Assignment operator of Iterator to HashMap.
			* @param obj is the Iterator on the right hand side to copy from.
			* @return returns this Iterator.
			*/
			Iterator& operator=(const Iterator& obj);

			/**
			* Equality operator of the Iterator to the HashMap.
			* @param obj is the Iterator on the right hand side to compare to.
			* @return returns true if not equal
			*/
			bool operator==(const Iterator& obj) const;

			/**
			* Inequality operator of the Iterator to the HashMap.
			* @param obj is the Iterator on the right hand side to compare to.
			* @return returns true if not equal
			*/
			bool operator!=(const Iterator& obj) const;

			/**
			* Pre-Increment operator for Iterator to HashMap
			* @return returns the incremented value of the iterator.
			*/
			Iterator& operator++();

			/**
			* Post-increment operator for Iterator to the HashMap
			* @return returns the original value of the Iterator before incrementing
			*/
			Iterator operator++(int);

			/**
			* Dereference operator for the Iterator of the HashMap
			* @return std:pair of TKey and TData that the Iterator is at
			*/
			PairType& operator*();

			/**
			* Const version of the dereference operator
			* @return std::pair of TKey and TData that the Iteraator is at
			*/
			const PairType& operator*() const;

			/**
			* Dereference operator for the Iterator of the HashMap
			* @return pointer to std:pair of TKey and TData that the Iterator is at
			*/
			PairType* operator->();

			/**
			* Arrow operator for the Iterator of the HashMap
			* @return pointer to std::pair of TKey and TData that the Iterator is at
			*/
			const PairType* operator->() const;

		private:
			/**
			* Private constructor to create a custom iterator for a HashMap
			* @param the owner of the HashMap
			* @param Index the Iterator needs to be pointing to.
			*/
			Iterator(const HashMap* ownerMap, std::uint32_t index, typename ChainType::Iterator chainIterator);

			const HashMap* mOwnerMap;						/**< The pointer to the owner HashMap. */
			std::uint32_t mIndex;							/**< The index of the current pair being pointed to. */
			typename ChainType::Iterator mChainIterator;	/**< The Iterator of the SList in the. */
		};

		/**
		* Constructor of the HashMap with a user-defined size(default size is 11)
		* @param size of the Map.
		*/
		HashMap(std::uint32_t mapSize = 11);

		/**
		* Copy constructor of the HashMap
		* @param obj of type HashMap
		*/
		HashMap(const HashMap& obj);
		
		/**
		* Move constructor moves the hashmap data from the passed parameter to this.
		* @param obj the Rvalue reference of the Hashmap to copy from
		*/
		HashMap(HashMap&& obj);

		/**
		* Destructor of the HashMap
		*/
		~HashMap();

		/**
		* Assignment operator for HashMap.
		* @param HashMap on the right hand side.
		* @return Reference to this map.
		*/
		HashMap& operator=(const HashMap& obj);

		/**
		* Move operator moves the hashmap data from the passed parameter to this and returns this
		* @param obj the Rvalue reference of the Hashmap to copy from
		* @return Hashmap reference to this
		*/
		HashMap& operator=(HashMap&& obj);

		/**
		* Searches for the pair in the HashMap that contains the key provided.
		* @param address of the key to be searched for.
		* @return address of the iterator to the found key.
		*/
		Iterator find(const TKey& key) const;

		/**
		* Inserts the given element into the HashMap.
		* @param accepts a pair of TKey and TData to insert
		* @return an Iterator to the inserted pair
		*/
		Iterator insert(const PairType& pair);

		/**
		* Inserts the given element into the HashMap.
		* @param accepts a pair of TKey and TData to insert
		* @param inserted is true if a value was inserted. It is an output parameter.
		* @return an Iterator to the inserted pair
		*/
		Iterator insert(const PairType& pair, bool& inserted);

		/**
		* Index operator returns the data associated to a key in the HashMap.
		* @param key that the lookup will be based on.
		* @return address of TData that found with the key.
		*/
		TData& operator[](const TKey& key);

		/**
		* Const version of the index operator for const HashMaps
		* @param key that the lookup will be based on.
		* @return const address of TData that found with the key.
		*/
		const TData& operator[](const TKey& key) const;

		/**
		* Remove the Pair associated with the key from the Map.
		* @param key passed to search the value.
		*/
		void remove(const TKey& key);

		/**
		* Clears the list of all elements.
		*/
		void clear();

		/**
		* Returns the current number of elements in the Bucket.
		* @return an unsigned integer containing size
		*/
		std::uint32_t size() const;

		/**
		* Checks if the key is present in the Map or not.
		* @param the key to be searched for.
		* @return true if the key is found.
		*/
		bool containsKey(const TKey& key) const;

		/**
		* Returns Iterator to the beginning of the HashMap
		* @return returns the address of the begin iterator
		*/
		Iterator begin() const;

		/**
		* Returns the end of the Chain at the last index of Bucket
		* @return returns the address of the end Iterator
		*/
		Iterator end() const;

	private:
		Iterator find(const TKey& key, std::uint32_t& index) const;
		std::uint32_t hashedValue(const TKey& key) const;

		BucketType mBucket;				/**< Vector that holds the Chains (SLists)	*/
		std::uint32_t mSize;			/**< Number of elements in the Vector		*/
	};

	template <typename T>
	class DefaultCompare
	{
	public:
		bool operator()(const T& first, const T& second);
	};

	template <>
	class DefaultCompare <char*>
	{
	public:
		bool operator()(const char* first, const char* second);
	};
}

#include "HashMap.inl"
namespace MahatmaGameEngine 
{
#pragma region Iterator
	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::Iterator() :
		mOwnerMap(nullptr), mIndex(0)
	{
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::Iterator(const HashMap* ownerMap, std::uint32_t index, typename ChainType::Iterator chainIterator) :
		mOwnerMap(ownerMap), mIndex(index), mChainIterator(chainIterator)
	{
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::Iterator(const Iterator& obj) :
		mOwnerMap(obj.mOwnerMap), mIndex(obj.mIndex), mChainIterator(obj.mChainIterator)
	{
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator=(const Iterator& obj)
	{
		if (this != &obj)
		{
			mOwnerMap = obj.mOwnerMap;
			mIndex = obj.mIndex;
			mChainIterator = obj.mChainIterator;
		}
		return *this;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	bool HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator==(const Iterator& obj) const
	{
		return ((mOwnerMap == obj.mOwnerMap) && (mIndex == obj.mIndex) && (mChainIterator == obj.mChainIterator));
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	bool HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator!=(const Iterator& obj) const
	{
		return !(*this == obj);
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator++()
	{
		if (this->mOwnerMap == nullptr)
		{
			throw std::runtime_error("Iterator not initialized.");
		}

		if (*this == mOwnerMap->end())
		{
			throw std::runtime_error("Index out of bounds");
		}

		if ((++mChainIterator != mOwnerMap->mBucket[mIndex].end()))
		{
			return *this;
		}
		++mIndex;

		uint32_t bucketSize = mOwnerMap->mBucket.size();
		//For the next indices in the mBucket.
		while(mIndex < bucketSize)
		{
			//Check if the current Chain Iterator is at end() and then check if its increment is at end().
			if(mOwnerMap->mBucket[mIndex].size() > 0)
			{
				mChainIterator = mOwnerMap->mBucket[mIndex].begin();
				break;
			}
			++mIndex;
			mChainIterator = mOwnerMap->mBucket[mIndex - 1].end();
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator++(int)
	{
		Iterator temp = *this;

		//For the next indices in the mBucket.
		this->operator++();

		return temp;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::PairType& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator*()
	{
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	const typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::PairType& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator*() const
	{
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::PairType* HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator->()
	{
		return &(*mChainIterator);
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	const typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::PairType* HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator::operator->() const
	{
		return &(*mChainIterator);
	}

#pragma endregion

#pragma region HashMap
	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::HashMap(std::uint32_t mapSize) :
		mSize(0)
	{
		mBucket.reserve(mapSize);

		//Initialize the fixed size vector with empty SLists.
		for (std::uint32_t i = 0; i < mapSize; ++i)
		{
			SList<std::pair<TKey, TData>> temp;
			mBucket.pushBack(temp);
		}
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::HashMap(const HashMap& obj) :
		mSize(obj.mSize), mBucket(obj.mBucket)
	{
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	HashMap<TKey, TData, HashFunction, ComparisonFunctor>::~HashMap()
	{
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::operator=(const HashMap& obj)
	{
		if (this != &obj)
		{
			mSize = obj.mSize;
			mBucket = obj.mBucket;
			return *this;
		}
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::begin() const
	{
		ChainType::Iterator tempIt;
		std::uint32_t index;

		if (mSize == 0)
		{
			return end();
		}

		for (index = 0; index < mBucket.size(); ++index)
		{
			tempIt = mBucket[index].begin();
			if (tempIt != mBucket[index].end())
			{
				break;
			}
		}

		return Iterator(this, index, tempIt);
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::end() const
	{
		return Iterator(this, mBucket.size(), mBucket[mBucket.size() - 1].end());
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	std::uint32_t HashMap<TKey, TData, HashFunction, ComparisonFunctor>::size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	bool HashMap<TKey, TData, HashFunction, ComparisonFunctor>::containsKey(const TKey& key) const
	{
		return (find(key) != end());
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::find(const TKey& key) const
	{
		std::uint32_t index = hashedValue(key);
		ComparisonFunctor compare;
		ChainType::Iterator chainIt = mBucket[index].begin();

		for (const auto& value : mBucket[index])
		{
			if (compare(value.first, key))
			{
				return Iterator(this, index, chainIt);
			}
			++chainIt;
		}
		
		return end();
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::find(const TKey& key, std::uint32_t& index) const
	{
		index = hashedValue(key);
		ComparisonFunctor compare;
		ChainType::Iterator chainIt = mBucket[index].begin();

		for (const auto& value : mBucket[index])
		{
			if (compare(value.first, key))
			{
				return Iterator(this, index, chainIt);
			}
			++chainIt;
		}

		return end();
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::insert(const PairType& pair)
	{
		std::uint32_t index;
		Iterator temp = find(pair.first, index);
		if (temp != end())
		{
			return temp;
		}
		++mSize;
		return Iterator(this, index, mBucket[index].pushBack(pair));
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	typename HashMap<TKey, TData, HashFunction, ComparisonFunctor>::Iterator HashMap<TKey, TData, HashFunction, ComparisonFunctor>::insert(const PairType& pair, bool& inserted)
	{
		std::uint32_t index;
		Iterator temp = find(pair.first, index);
		if (temp != end())
		{
			inserted = false;
			return temp;
		}
		++mSize;
		inserted = true;
		return Iterator(this, index, mBucket[index].pushBack(pair));
	}
	
	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	TData& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::operator[](const TKey& key)
	{			
		return (*insert(PairType(key, TData()))).second;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	const TData& HashMap<TKey, TData, HashFunction, ComparisonFunctor>::operator[](const TKey& key) const
	{
		return (*find(key)).second;
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	void HashMap<TKey, TData, HashFunction, ComparisonFunctor>::remove(const TKey& key)
	{
		Iterator temp = find(key);
		if (temp == end())
		{
			return;
		}
		else
		{
			mBucket[temp.mIndex].remove(*temp);
		}
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	void HashMap<TKey, TData, HashFunction, ComparisonFunctor>::clear()
	{
		for (auto& value : mBucket)
		{
			value.clear();
		}
	}

	template <typename TKey, typename TData, typename HashFunction, typename ComparisonFunctor>
	std::uint32_t HashMap<TKey, TData, HashFunction, ComparisonFunctor>::hashedValue(const TKey& key) const
	{
		//static because only one instance on hash is required
		static HashFunction hash;
		return (hash(key) % mBucket.size());
	}

	template<typename T>
	inline bool DefaultCompare<T>::operator()(const T& first, const T& second)
	{
		return (first == second);
	}

	inline bool DefaultCompare<char*>::operator()(const char* first, const char* second)
	{
		return (strcmp(first, second) == 0);
	}

#pragma endregion
}
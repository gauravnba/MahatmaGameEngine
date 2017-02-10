namespace MahatmaGameEngine 
{
#pragma region Iterator
	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::Iterator::Iterator() :
		mOwnerMap(nullptr), mIndex(0)
	{
	}

	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::Iterator::Iterator(const HashMap* ownerMap, std::uint32_t index, typename ChainType::Iterator chainIterator) :
		mOwnerMap(ownerMap), mIndex(index), mChainIterator(chainIterator)
	{
	}

	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::Iterator::Iterator(const Iterator& obj) :
		mOwnerMap(obj.mOwnerMap), mIndex(obj.mIndex), mChainIterator(obj.mChainIterator)
	{
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator& HashMap<TKey, TData, HashFunction>::Iterator::operator=(const Iterator& obj)
	{
		mOwnerMap = obj.mOwnerMap;
		mIndex = obj.mIndex;
		mChainIterator = obj.mChainIterator;
		return *this;
	}

	template <typename TKey, typename TData, typename HashFunction>
	bool HashMap<TKey, TData, HashFunction>::Iterator::operator==(const Iterator& obj) const
	{
		return ((mOwnerMap == obj.mOwnerMap) && (mIndex == obj.mIndex) && (mChainIterator == obj.mChainIterator));
	}

	template <typename TKey, typename TData, typename HashFunction>
	bool HashMap<TKey, TData, HashFunction>::Iterator::operator!=(const Iterator& obj) const
	{
		return !(*this == obj);
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator& HashMap<TKey, TData, HashFunction>::Iterator::operator++()
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

		//For the next indices in the mBucket.
		while(mIndex < mOwnerMap->mBucket.size())
		{
			//Check if the current Chain Iterator is at end() and then check if its increment is at end().
			if(mOwnerMap->mBucket[mIndex].size() > 0)
			{
				mChainIterator = mOwnerMap->mBucket[mIndex].begin();
				break;
			}
			++mIndex;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator HashMap<TKey, TData, HashFunction>::Iterator::operator++(int)
	{
		Iterator temp = *this;

		//For the next indices in the mBucket.
		this->operator++();

		return temp;
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::PairType& HashMap<TKey, TData, HashFunction>::Iterator::operator*()
	{
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename HashFunction>
	const typename HashMap<TKey, TData, HashFunction>::PairType& HashMap<TKey, TData, HashFunction>::Iterator::operator*() const
	{
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::PairType* HashMap<TKey, TData, HashFunction>::Iterator::operator->()
	{
		return &(*mChainIterator);
	}

	template <typename TKey, typename TData, typename HashFunction>
	const typename HashMap<TKey, TData, HashFunction>::PairType* HashMap<TKey, TData, HashFunction>::Iterator::operator->() const
	{
		return &(*mChainIterator);
	}

#pragma endregion

#pragma region HashMap
	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::HashMap(std::uint32_t mapSize) :
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

	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::HashMap(const HashMap& obj) :
		mSize(obj.mSize), mBucket(obj.mBucket)
	{
	}

	template <typename TKey, typename TData, typename HashFunction>
	HashMap<TKey, TData, HashFunction>::~HashMap()
	{
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>& HashMap<TKey, TData, HashFunction>::operator=(const HashMap& obj)
	{
		mSize = obj.mSize;
		mBucket = obj.mBucket;
		return *this;
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator HashMap<TKey, TData, HashFunction>::begin() const
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

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator HashMap<TKey, TData, HashFunction>::end() const
	{

		return Iterator(this, mBucket.size(), mBucket[mBucket.size() - 1].end());
	}

	template <typename TKey, typename TData, typename HashFunction>
	std::uint32_t HashMap<TKey, TData, HashFunction>::size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename HashFunction>
	bool HashMap<TKey, TData, HashFunction>::containsKey(const TKey& key) const
	{
		return (find(key) != end());
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator HashMap<TKey, TData, HashFunction>::find(const TKey& key) const
	{
		std::uint32_t index = hashedValue(key);
		ChainType::Iterator chainIt = mBucket[index].begin();

		for (const auto& value : mBucket[index])
		{
			if (value.first == key)
			{
				break;
			}
			++chainIt;
		}

		if (chainIt == mBucket[index].end())
		{
			return end();
		}

		return Iterator(this, index, chainIt);
	}

	template <typename TKey, typename TData, typename HashFunction>
	typename HashMap<TKey, TData, HashFunction>::Iterator HashMap<TKey, TData, HashFunction>::insert(const PairType& pair)
	{
		Iterator temp = find(pair.first);
		if (temp != end())
		{
			return temp;
		}
		std::uint32_t index = hashedValue(pair.first);
		++mSize;
		return Iterator(this, index, mBucket[index].pushBack(pair));
	}
	
	template <typename TKey, typename TData, typename HashFunction>
	TData& HashMap<TKey, TData, HashFunction>::operator[](const TKey& key)
	{			
		return (*insert(PairType(key, TData()))).second;
	}

	template <typename TKey, typename TData, typename HashFunction>
	const TData& HashMap<TKey, TData, HashFunction>::operator[](const TKey& key) const
	{
		return (*find(key)).second;
	}


	template <typename TKey, typename TData, typename HashFunction>
	void HashMap<TKey, TData, HashFunction>::remove(const TKey& key)
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

	template <typename TKey, typename TData, typename HashFunction>
	void HashMap<TKey, TData, HashFunction>::clear()
	{
		for (auto& value : mBucket)
		{
			value.clear();
		}
	}

	template <typename TKey, typename TData, typename HashFunction>
	std::uint32_t HashMap<TKey, TData, HashFunction>::hashedValue(const TKey& key) const
	{
		//static because only one instance on hash is required
		static HashFunction hash;
		return (hash(key) % mBucket.size());
	}

#pragma endregion
}


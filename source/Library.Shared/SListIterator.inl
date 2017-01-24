namespace MahatmaGameEngine

{
	template<typename T>
	SList<T>::Iterator::Iterator() :
		mCurrentNode(nullptr), mCurrentList(nullptr)
	{
	}

	template <typename T>
	SList<T>::Iterator::Iterator(Node* node, SList<T>* list) :
		mCurrentNode(node), mCurrentList(list)
	{
	}

	template <typename T>
	SList<T>::Iterator::~Iterator()
	{
	}

	template <typename T>
    SList<T>::Iterator::Iterator(const typename SList<T>::Iterator& obj) :
		mCurrentNode(obj.mCurrentNode), mCurrentList(obj.mCurrentList)
	{
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const typename SList<T>::Iterator& obj)
	{
		if ((mCurrentList != nullptr) && (obj.mCurrentList != mCurrentList))
		{
			throw std::runtime_error("The iterator passed as argument belongs to a different list.");
		}

		if (*this != obj)
		{
			mCurrentList = obj.mCurrentList;
			mCurrentNode = obj.mCurrentNode;
		}
		return *this;
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const typename SList<T>::Iterator& obj) const
	{
		if ((mCurrentNode == obj.mCurrentNode) && (mCurrentList == obj.mCurrentList))
		{
			return true;
		}
		return false;
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const typename SList<T>::Iterator& obj) const
	{
		if ((mCurrentNode == obj.mCurrentNode) && (mCurrentList == obj.mCurrentList))
		{
			return false;
		}
		return true;
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is pointing to null.");
		}
		
		mCurrentNode = mCurrentNode->next;
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int temp)
	{
		temp;//Unused parameter

		Iterator tempNode = *this;

		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is not initialized.");
		}
		
		mCurrentNode = mCurrentNode->next;
		return tempNode;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is pointing to null.");
		}
		return mCurrentNode->item;
	}
}
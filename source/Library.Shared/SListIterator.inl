namespace MahatmaGameEngine

{
	template<typename T>
	SList<T>::Iterator::Iterator() :
		mCurrentNode(nullptr), mCurrentList(nullptr)
	{
	}

	template <typename T>
	SList<T>::Iterator::Iterator(Node* node, const SList<T>* list) :
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
		return ((mCurrentNode == obj.mCurrentNode) && (mCurrentList == obj.mCurrentList));
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const typename SList<T>::Iterator& obj) const
	{
		return !(*this == obj);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is pointing to null.");
		}

		if (mCurrentNode->next == nullptr)
		{
			mCurrentNode = nullptr;
		}
		else
		{
			mCurrentNode = mCurrentNode->next;
		}
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator tempNode = *this;

		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is not initialized.");
		}

		if (mCurrentNode->next == nullptr)
		{
			mCurrentNode = nullptr;
		}
		else
		{
			mCurrentNode = mCurrentNode->next;
		}

		return tempNode;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*()
	{
		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is pointing to null.");
		}
		return mCurrentNode->item;
	}

	template <typename T>
	const T& SList<T>::Iterator::operator*() const
	{
		if (mCurrentNode == nullptr)
		{
			throw std::runtime_error("The iterator is pointing to null.");
		}
		return mCurrentNode->item;
	}
}
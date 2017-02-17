namespace MahatmaGameEngine
{
	template <typename T>
	SList<T>::Node::Node() :
		next(nullptr)
	{
	}

	template <typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template <typename T>
	SList<T>::SList(const SList<T> &obj) :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
		Node* temp = obj.mFront;
		while ( temp != nullptr )
		{
			pushBack(temp->item);
			temp = temp->next;
		}
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList<T>& obj)
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
	SList<T>::~SList()
	{
		//Remove all nodes from front to back.
		while(mFront != nullptr)
		{
			Node* temp = mFront;
			mFront = temp->next;
			delete temp;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::pushFront(const T& data)
	{
		Node* temp = new Node;
		temp->item = data;
		temp->next = mFront;
		mFront = temp;
		if (mSize == 0)
		{
			mBack = mFront;
		}

		++mSize;
		return begin();
	}

	template <typename T>
	T SList<T>::popFront()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("You attempted to pop an item from an empty list.");
		}

		Node* temp = mFront;
		T returnItem = temp->item;

		mFront = temp->next;
		delete temp;

		--mSize;

		//If there are no elements in the list, have the front and back point to nullptr.
		if (mSize == 0)
		{
			mFront = nullptr;
			mBack = nullptr;
		}

		return returnItem;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::pushBack(const T& data)
	{
		Node* temp	= new Node;

		temp->item	= data;
		if (mSize != 0)
		{
			mBack->next = temp;
			mBack = temp;
		}
		else
		{
			mBack = temp;
			mFront = mBack;
		}

		++mSize;

		return Iterator(mBack, this);
	}

	template <typename T>
	void SList<T>::clear()
	{
		//Remove all nodes from front to back.
		while(mFront != nullptr)
		{
			Node* temp = mFront;
			mFront = temp->next;
			delete temp;
		}

		//Reset the member variables.
		mFront = nullptr;
		mBack = nullptr;
		mSize = 0;
	}

	template <typename T>
	std::uint32_t SList<T>::size() const
	{
		return mSize;
	}

	template <typename T>
	bool SList<T>::isEmpty() const
	{
		if (mSize == 0)
		{
			return true;
		}
		return false;
	}

	template <typename T>
	T& SList<T>::front()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("You attempted to get an item from an empty list.");
		}
		return (mFront->item);
	}

	template <typename T>
	T& SList<T>::back()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("You attempted to get an item from an empty list.");
		}
		return (mBack->item);
	}

	template <typename T>
	const T& SList<T>::front() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("You attempted to get an item from an empty list.");
		}
		return (const T&)(mFront->item);
	}

	template <typename T>
	const T& SList<T>::back() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("You attempted to get an item from an empty list.");
		}
		return (const T&)(mBack->item);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(mFront, this);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		if (mSize == 0)
		{
			return begin();
		}
		return Iterator(mBack->next, this);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::insertAfter(const Iterator& it, T data)
	{
		if (it.mCurrentList != this)
		{
			throw std::runtime_error("The iterator argument passed belongs to another list.");
		}

		//Case: if the iterator is pointing to null, pushBack.
		if (it.mCurrentNode == nullptr)
		{
			return pushBack(data);
		}

		Node* temp = new Node;
		temp->item = data;
		temp->next = it.mCurrentNode->next;
		it.mCurrentNode->next = temp;

		//Case: If there is only one element in the list, assign mBack as temp.
		if (mFront == mBack)
		{
			mBack = temp;
		}

		++mSize;

		return Iterator(temp, this);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::find(const T& value)
	{
		if (begin().mCurrentNode == nullptr)
		{
			return end();
		}

		Iterator it = begin();

		while (it != end())
		{
			if (*it == value)
			{
				//If reached the end of the list, the value was not found. Return end.
				break;
			}
			++it;
		}
		return it;
	}

	template <typename T>
	void SList<T>::remove(const T& value)
	{
		if (begin().mCurrentNode == nullptr)
		{
			return;
		}

		Iterator it = begin();
		Iterator previous = begin(); //iterator to the node, previous to the one where the value was found.

		while (it != end())
		{
			if (*it == value)
			{
				//If reached the end of the list, the value was not found. Return to caller.
				break;
			}

			previous = it++;
		}

		previous.mCurrentNode->next = it.mCurrentNode->next;
		delete it.mCurrentNode;

		--mSize;
		if (mSize == 1)
		{
			mBack = mFront;
		}
		//If the list is empty, the mFront and the mBack need to be reinitialized to nullptr.
		if (mSize == 0)
		{
			mFront = nullptr;
			mBack = nullptr;
		}
	}
}
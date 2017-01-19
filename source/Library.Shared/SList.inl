namespace MahatmaGameEngine
{
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
	SList<T>& SList<T>::operator=(const SList<T> &obj)
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
	void SList<T>::pushFront(T data)
	{
		Node* temp = new Node;
		temp->item = data;
		temp->next = mFront;
		mFront = temp;
		if (mSize == 0)
		{
			mBack = mFront;
		}

		mSize++;
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

		mSize--;

		//If there are no elements in the list, have the front and back point to nullptr.
		if (mSize == 0)
		{
			mFront = nullptr;
			mBack = nullptr;
		}

		return returnItem;
	}

	template <typename T>
	void SList<T>::pushBack(T data)
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

		mSize++;
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
}
#include "Vector.h"
namespace MahatmaGameEngine
{
#pragma region Iterator
	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mIndex(0), mVector(nullptr)
	{
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(std::uint32_t index, Vector<T>* vector) :
		mIndex(index), mVector(vector)
	{
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(const typename Vector<T>::Iterator& obj) :
		mIndex(obj.mIndex), mVector(obj.mVector)
	{
	}

	template <typename T>
	Vector<T>::Iterator::~Iterator()
	{
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const typename Vector<T>::Iterator& obj)
	{
		if (this != &obj)
		{
			mIndex = obj.mIndex;
			mVector = obj.mVector;
		}
		return *this;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const typename Vector<T>::Iterator& obj) const
	{
		return ((mIndex == obj.mIndex) && (mVector == obj.mVector));
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const typename Vector<T>::Iterator& obj) const
	{
		return !(*this == obj);
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mVector == nullptr)
		{
			throw std::runtime_error("Iterator is uninitialized.");
		}

		++mIndex;

		if (mIndex > (mVector->mSize))
		{
			throw std::runtime_error("Iterator went out of bounds of the vector.");
		}

		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		if (mVector == nullptr)
		{
			throw std::runtime_error("Iterator is uninitialized.");
		}

		Iterator tempIt = *this;

		++mIndex;

		if (mIndex == (mVector->mSize))
		{
			throw std::runtime_error("Iterator went out of bounds of the vector.");
		}
		return tempIt;
	}

	template <typename T>
	typename T& Vector<T>::Iterator::operator*() const
	{
		if (mVector == nullptr)
		{
			throw std::runtime_error("The Iterator is uninitialized.");
		}

		if (mIndex >= mVector->mSize)
		{
			throw std::runtime_error("Trying to dereference invalid pointer.");
		}
		return mVector->mArray[mIndex];
	}
#pragma endregion

#pragma region Vector
	template <typename T>
	Vector<T>::Vector() :
		mSize(0), mCapacity(0), mArray(nullptr)
	{
		reserve(mCapacity);
	}

	template <typename T>
	Vector<T>::Vector(const Vector& obj) :
		mSize(0), mCapacity(obj.mCapacity), mArray(nullptr)
	{
		reserve(mCapacity);
		for (const T& value : obj)
		{
			pushBack(value);
		}
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		clear();
		free(mArray);
	}

	template <typename T>
	void Vector<T>::reserve(std::uint32_t capacity)
	{
		if (capacity < mSize)
		{
			throw std::runtime_error("Can't reserve memory lower than the size of the vector.");
		}
		mArray = static_cast<T*>(realloc(mArray, (capacity * sizeof(T))));

		mCapacity = capacity;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& obj)
	{
		if (this != &obj)
		{
			clear();
			reserve(obj.mCapacity);
			for (const T& value : obj)
			{
				pushBack(value);
			}
		}
		return *this;
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::runtime_error("The index is out of bounds.");
		}
		return mArray[index];
	}

	template <typename T>
	const T& Vector<T>::operator[](std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::runtime_error("The index is out of bounds.");
		}
		return mArray[index];
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(0, const_cast<Vector<T>*>(this));
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		if (mSize == 0)
		{
			begin();
		}
		return Iterator(mSize, const_cast<Vector<T>*>(this));
	}

	template <typename T>
	std::uint32_t Vector<T>::size()
	{
		return mSize;
	}

	template <typename T>
	std::uint32_t Vector<T>::capacity()
	{
		return mCapacity;
	}

	template <typename T>
	bool Vector<T>::isEmpty()
	{
		if (mSize == 0)
		{
			return true;
		}
		return false;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::pushBack(const T& data)
	{
		if (mSize == mCapacity)
		{
			reserve(mCapacity + mIncreaseBy);
		}
		new(&mArray[mSize]) T();
		mArray[mSize] = data;
		++mSize;
		return Iterator(mSize - 1, this);
	}

	template <typename T>
	T Vector<T>::popBack()
	{
		T temp = mArray[--mSize];
		mArray[mSize].~T();
		return temp;
	}

	template <typename T>
	T& Vector<T>::front()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No elements present in the vector.");
		}
		return mArray[0];
	}

	template <typename T>
	const T& Vector<T>::front() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No elements present in the vector.");
		}
		return mArray[0];
	}

	template <typename T>
	T& Vector<T>::back()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No elements present in the vector.");
		}
		return mArray[mSize - 1];
	}

	template <typename T>
	const T& Vector<T>::back() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No elements present in the vector.");
		}
		return mArray[mSize - 1];
	}

	template <typename T>
	void Vector<T>::clear()
	{
		while (mSize != 0)
		{
			popBack();
		}
		mCapacity = mIncreaseBy;
		reserve(mCapacity);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::find(const T& item) const
	{
		std::uint32_t i = 0;
		for(auto &value: *this)
		{
			if (value == item)
			{
				break;
			}
			++i;
		}
		return Iterator(i, const_cast<Vector<T>*>(this));
	}

	template <typename T>
	void Vector<T>::remove(const T& item)
	{
		Iterator it = find(item);
		if (it != end())
		{
			(*it).~T();
			Iterator source = it++;
			memmove(&mArray[source.mIndex], &mArray[it.mIndex], (mSize - it.mIndex) * sizeof(T));
			--mSize;
		}
	}
#pragma endregion
}
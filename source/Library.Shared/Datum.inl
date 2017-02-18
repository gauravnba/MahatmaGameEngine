namespace MahatmaGameEngine
{
	template <typename T>
	void Datum::instantiateSize(T* datumVal, std::uint32_t size)
	{
		while (mSize < size)
		{
			new(&datumVal[mSize++]) T();
		}
	}

	template <typename T>
	void Datum::removeRecursively(T* datumVal, std::uint32_t size)
	{
		while (mSize > size)
		{
			datumVal[--mSize].~T();
		}
	}

	//template <typename T>
	//bool Datum::remove(std::uint32_t index)
	//{
	//	if (index < mSize)
	//	{
	//		mDatumVal.genericType[index].~T;
	//		memmove(&mDatumVal.genericType[index], &mDatumVal.genericType[index + 1], (mSize - index) * sizeof(T));
	//		return true;
	//	}
	//	return false;
	//}

#pragma region GET_TEMPLATES
	template <typename T>
	T& Datum::get(std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Invalid type.");
	}

	template <>
	std::int32_t& Datum::get<std::int32_t>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.integerType[index];
	}

	template <>
	float& Datum::get<float>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.floatingType[index];
	}

	template <>
	glm::vec4& Datum::get<glm::vec4>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.vectorType[index];
	}

	template <>
	glm::mat4x4& Datum::get<glm::mat4x4>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.matrixType[index];
	}

	template <>
	Scope*& Datum::get<Scope*>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.tableType[index];
	}

	template <>
	std::string& Datum::get<std::string>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.stringType[index];
	}

	template <>
	RTTI*& Datum::get<RTTI*>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.rttiType[index];
	}
#pragma endregion

#pragma region CONST_GET_TEMPLATES
	template <typename T>
	const T& Datum::get(std::uint32_t index) const
	{
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Invalid type.");
	}

	template <>
	const std::int32_t& Datum::get<std::int32_t>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.integerType[index];
	}

	template <>
	const float& Datum::get<float>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.floatingType[index];
	}

	template <>
	const glm::vec4& Datum::get<glm::vec4>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.vectorType[index];
	}

	template <>
	const glm::mat4x4& Datum::get<glm::mat4x4>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.matrixType[index];
	}

	template <>
	Scope* const& Datum::get<Scope*>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.tableType[index];
	}

	template <>
	const std::string& Datum::get<std::string>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.stringType[index];
	}

	template <>
	RTTI* const& Datum::get<RTTI*>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		return mDatumVal.rttiType[index];
	}
#pragma endregion
}
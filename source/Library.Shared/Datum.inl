#pragma once
namespace MahatmaGameEngine
{
#pragma region GET_TEMPLATES
	template <>
	std::int32_t& Datum::get<std::int32_t>(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		if (mType != DatumType::INTEGER)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::FLOAT)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::VECTOR)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::MATRIX)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::TABLE)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::STRING)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::RTTI_POINTER)
		{
			throw std::runtime_error("Invalid type");
		}
		return mDatumVal.rttiType[index];
	}
#pragma endregion

#pragma region CONST_GET_TEMPLATES
	template <>
	const std::int32_t& Datum::get<std::int32_t>(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index was out of range.");
		}
		if (mType != DatumType::INTEGER)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::FLOAT)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::VECTOR)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::MATRIX)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::TABLE)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::STRING)
		{
			throw std::runtime_error("Invalid type");
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
		if (mType != DatumType::RTTI_POINTER)
		{
			throw std::runtime_error("Invalid type");
		}
		return mDatumVal.rttiType[index];
	}
#pragma endregion
}
#include "pch.h"

#include "Datum.h"
#include <exception>

using namespace MahatmaGameEngine;
using namespace glm;
using namespace std;
using namespace Library;

Datum::Datum() :
	mIsExternal(false), mType(DatumType::UNKNOWN), mSize(0), mCapacity(0)
{
	mDatumVal.genericType = nullptr;
}

Datum::~Datum()
{
	if (!mIsExternal)
	{
		clear();
		free(mDatumVal.genericType);
	}
}

Datum::Datum(const Datum& obj) :
	mIsExternal(obj.mIsExternal), mType(obj.mType), mSize(0), mCapacity(0)
{
	mDatumVal.genericType = nullptr;
	switch (mType)
	{
	case DatumType::INTEGER:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.integerType[mSize], mSize);
		}
		break;
	case DatumType::FLOAT:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.floatingType[mSize], mSize);
		}
		break;
	case DatumType::VECTOR:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.vectorType[mSize], mSize);
		}
		break;
	case DatumType::MATRIX:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.matrixType[mSize], mSize);
		}
		break;
	case DatumType::STRING:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.stringType[mSize], mSize);
		}
		break;
	case DatumType::RTTI_POINTER:
		while (mSize < obj.mSize)
		{
			set(obj.mDatumVal.rttiType[mSize], mSize);
		}
		break;
	}
}

/********************************** Assignment operator definitions **************************************/
Datum& Datum::operator=(const Datum& obj)
{
	if (this != &obj)
	{
		clear();
		switch (obj.mType)
		{
		case DatumType::INTEGER:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.integerType[mSize], mSize);
			}
			break;
		case DatumType::FLOAT:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.floatingType[mSize], mSize);
			}
			break;
		case DatumType::VECTOR:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.vectorType[mSize], mSize);
			}
			break;
		case DatumType::MATRIX:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.matrixType[mSize], mSize);
			}
			break;
		case DatumType::STRING:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.stringType[mSize], mSize);
			}
			break;
		case DatumType::RTTI_POINTER:
			while (mSize < obj.mSize)
			{
				set(obj.mDatumVal.rttiType[mSize], mSize);
			}
			break;
		default:
			throw runtime_error("Invalid type assignment");
			break;
		}
	}
	return *this;
}

Datum& Datum::operator=(int32_t obj)
{
	set(obj);
	return *this;
}

Datum& Datum::operator=(const float& obj)
{
	set(obj);
	return *this;
}

Datum& Datum::operator=(const vec4& obj)
{
	set(obj);
	return *this;
}

Datum& Datum::operator=(const mat4x4& obj)
{
	set(obj);
	return *this;
}

Datum& Datum::operator=(const string& obj)
{
	set(obj);
	return *this;
}

Datum& Datum::operator=(RTTI* obj)
{
	set(obj);
	return *this;
}

/********************************** Equality operator definitions ***********************************/

bool Datum::operator==(const Datum& obj) const
{
	bool isEqual = false;
	if ((this != &obj) && (mType == obj.mType))
	{
		uint32_t i = 0;
		switch (mType)
		{
		case DatumType::INTEGER:
			while (i < mSize)
			{
				if (mDatumVal.integerType[i] != obj.mDatumVal.integerType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;

		case DatumType::FLOAT:
			while (i < mSize)
			{
				if (mDatumVal.floatingType[i] != obj.mDatumVal.floatingType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;

		case DatumType::VECTOR:
			while (i < mSize)
			{
				if (mDatumVal.vectorType[i] != obj.mDatumVal.vectorType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;

		case DatumType::MATRIX:
			while (i < mSize)
			{
				if (mDatumVal.matrixType[i] != obj.mDatumVal.matrixType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;

		case DatumType::STRING:
			while (i < mSize)
			{
				if (mDatumVal.stringType[i] != obj.mDatumVal.stringType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;

		case DatumType::RTTI_POINTER:
			while (i < mSize)
			{
				if (mDatumVal.rttiType[i] == obj.mDatumVal.rttiType[i])
				{
					isEqual = false;
					break;
				}
				++i;
				isEqual = true;
			}
			break;
		}
	}
	return isEqual;
}

bool Datum::operator==(int32_t obj) const
{
	return (mDatumVal.integerType[0] == obj);
}

bool Datum::operator==(const float& obj) const
{
	return (mDatumVal.floatingType[0] == obj);
}

bool Datum::operator==(const vec4& obj) const
{
	return (mDatumVal.vectorType[0] == obj);
}

bool Datum::operator==(const mat4x4& obj) const
{
	return (mDatumVal.matrixType[0] == obj);
}

bool Datum::operator==(const string& obj) const
{
	return (mDatumVal.stringType[0] == obj);
}

bool Datum::operator==(const RTTI* obj) const
{
	return (mDatumVal.rttiType[0] == obj);
}

/********************************** Inequality operator definitions *********************************/

bool Datum::operator!=(const Datum& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(int32_t obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const float& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const vec4& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const mat4x4& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const string& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const RTTI* obj) const
{
	return (!(*this == obj));
}

void Datum::setType(DatumType datumType)
{
	if ((mType != DatumType::UNKNOWN) && (mType != datumType))
	{
		throw runtime_error("DatumType already set to another type.");
	}
	mType = datumType;
}

DatumType Datum::type() const
{
	return mType;
}

void Datum::setSize(uint32_t size)
{
	switch (mType)
	{
	case DatumType::INTEGER:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.integerType = static_cast<int32_t*>(realloc(mDatumVal.integerType, mCapacity * sizeof(int32_t)));
		}
		instantiateSize<int32_t>(mDatumVal.integerType, size);
		removeRecursively<int32_t>(mDatumVal.integerType, size);
		break;

	case DatumType::FLOAT:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.floatingType = static_cast<float*>(realloc(mDatumVal.floatingType, mCapacity * sizeof(float)));
		}
		instantiateSize<float>(mDatumVal.floatingType, size);
		removeRecursively<float>(mDatumVal.floatingType, size);
		break;

	case DatumType::VECTOR:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.vectorType = static_cast<vec4*>(realloc(mDatumVal.vectorType, mCapacity * sizeof(vec4)));
		}
		instantiateSize<vec4>(mDatumVal.vectorType, size);
		removeRecursively<vec4>(mDatumVal.vectorType, size);
		break;

	case DatumType::MATRIX:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.matrixType = static_cast<mat4x4*>(realloc(mDatumVal.matrixType, mCapacity * sizeof(mat4x4)));
		}
		instantiateSize<mat4x4>(mDatumVal.matrixType, size);
		removeRecursively<mat4x4>(mDatumVal.matrixType, size);
		break;

	case DatumType::TABLE:
		//Do nothing yet.
		break;

	case DatumType::STRING:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.stringType = static_cast<string*>(realloc(mDatumVal.stringType, mCapacity * sizeof(string)));
		}
		instantiateSize<string>(mDatumVal.stringType, size);
		removeRecursively<string>(mDatumVal.stringType, size);
		break;

	case DatumType::RTTI_POINTER:
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.rttiType = static_cast<RTTI**>(realloc(mDatumVal.rttiType, mCapacity * sizeof(RTTI*)));
		}
		instantiateSize<RTTI*>(mDatumVal.rttiType, size);
		removeRecursively<RTTI*>(mDatumVal.rttiType, size);
		break;

		//If no valid type was encountered.
	default:
		throw runtime_error("Invalid type");
	}
}

std::uint32_t Datum::size()
{
	return mSize;
}

std::uint32_t Datum::capacity()
{
	return mCapacity;
}

void Datum::clear()
{
	switch (mType)
	{
	case DatumType::INTEGER:
		removeRecursively<int32_t>(mDatumVal.integerType, 0);
		break;

	case DatumType::FLOAT:
		removeRecursively<float>(mDatumVal.floatingType, 0);
		break;
		
	case DatumType::VECTOR:
		removeRecursively<vec4>(mDatumVal.vectorType, 0);
		break;

	case DatumType::MATRIX:
		removeRecursively<mat4x4>(mDatumVal.matrixType, 0);
		break;

	case DatumType::STRING:
		removeRecursively<string>(mDatumVal.stringType, 0);
		break;

	case DatumType::RTTI_POINTER:
		removeRecursively<RTTI*>(mDatumVal.rttiType, 0);
		break;
	}
}

/******************************************* Overloaded functions - set *******************************************/

void Datum::set(int32_t value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::INTEGER))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::INTEGER;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.integerType[index] = value;
}

void Datum::set(const float& value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::FLOAT))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::FLOAT;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.floatingType[index] = value;
}

void Datum::set(const vec4& value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::VECTOR))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::VECTOR;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.vectorType[index] = value;
}

void Datum::set(const mat4x4& value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::MATRIX))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::MATRIX;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.matrixType[index] = value;
}

void Datum::set(const string& value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::STRING))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::STRING;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.stringType[index] = value;
}

void Datum::set(RTTI* value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::RTTI_POINTER))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::RTTI_POINTER;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.rttiType[index] = value;
}
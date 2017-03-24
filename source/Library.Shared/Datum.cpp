#include "pch.h"

#include "Datum.h"
#include "Scope.h"
#include <exception>
#include <sstream>

using namespace MahatmaGameEngine;
using namespace glm;
using namespace std;

Datum::Datum() :
	mIsExternal(false), mType(DatumType::UNKNOWN), mSize(0), mCapacity(0)
{
	mDatumVal.genericType = nullptr;
}

Datum::~Datum()
{
	if (!mIsExternal)
	{
		emptyOut();
	}
}

Datum::Datum(const Datum& obj) :
	mIsExternal(obj.mIsExternal), mType(obj.mType), mSize(0), mCapacity(0)
{
	mDatumVal.genericType = nullptr;
	switch (mType)
	{
	case DatumType::UNKNOWN:
		break;
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
	case DatumType::TABLE:
		while (mSize < obj.mSize)
		{
			set(*(obj.mDatumVal.tableType[mSize]), mSize);
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

Datum::Datum(Datum&& obj) : 
	mIsExternal(obj.mIsExternal), mType(obj.mType), mSize(obj.mSize), mCapacity(obj.mSize), mDatumVal(obj.mDatumVal)
{
	obj.mIsExternal = false;
	obj.mType = DatumType::UNKNOWN;
	obj.mSize = 0;
	obj.mCapacity = 0;
	obj.mDatumVal.genericType = nullptr;
}

#pragma region ASSIGNMENT_OPERATOR
Datum& Datum::operator=(const Datum& obj)
{
	if (this != &obj)
	{
		clear();
		switch (obj.mType)
		{
		case DatumType::UNKNOWN:
			break;
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
		case DatumType::TABLE:
			while (mSize < obj.mSize)
			{
				set(*(obj.mDatumVal.tableType[mSize]), mSize);
			}
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
	mIsExternal = obj.mIsExternal;

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

Datum& Datum::operator=(Scope& obj)
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
#pragma endregion

Datum& Datum::operator=(Datum&& obj)
{
	if (this != &obj)
	{
		emptyOut();

		mIsExternal = obj.mIsExternal;
		mSize		= obj.mSize;
		mCapacity	= obj.mCapacity;
		mType		= obj.mType;
		mDatumVal	= obj.mDatumVal;

		obj.mIsExternal = false;
		obj.mSize = 0;
		obj.mCapacity = 0;
		obj.mType = DatumType::UNKNOWN;
		obj.mDatumVal.genericType = nullptr;
	}
	return *this;
}

#pragma region EQUALITY_OPERATOR

bool Datum::operator==(const Datum& obj) const
{
	bool isEqual = true;
	if (this != &obj)
	{
		if (mType != obj.mType)
		{
			return false;
		}
		uint32_t i = 0;
		switch (mType)
		{
		case DatumType::UNKNOWN:
			break;

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

		case DatumType::TABLE:
			while (i < mSize)
			{
				if (!(mDatumVal.tableType[i]->equals(obj.mDatumVal.tableType[i])))
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
				if (!(mDatumVal.rttiType[i]->equals(obj.mDatumVal.rttiType[i])))
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

bool Datum::operator==(const Scope& obj) const
{
	return (mDatumVal.tableType[0]->equals(&obj));
}

bool Datum::operator==(const string& obj) const
{
	return (mDatumVal.stringType[0] == obj);
}

bool Datum::operator==(const RTTI* obj) const
{
	return ((obj != nullptr) && (mDatumVal.rttiType[0]->equals(obj)));
}

#pragma endregion

#pragma region INEQUALITY_OPERATOR

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

bool Datum::operator!=(const Scope& obj) const
{
	return !(*this == obj);
}

bool Datum::operator!=(const string& obj) const
{
	return (!(*this == obj));
}

bool Datum::operator!=(const RTTI* obj) const
{
	return (!(*this == obj));
}

#pragma endregion

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
		if (size > mCapacity)
		{
			mCapacity = size;
			mDatumVal.tableType = static_cast<Scope**>(realloc(mDatumVal.tableType, mCapacity * sizeof(Scope*)));
		}
		instantiateSize<Scope*>(mDatumVal.tableType, size);
		removeRecursively<Scope*>(mDatumVal.tableType, size);
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

std::uint32_t Datum::size() const
{
	return mSize;
}

std::uint32_t Datum::capacity() const
{
	return mCapacity;
}

void Datum::clear()
{
	switch (mType)
	{
	case DatumType::UNKNOWN:
		break;

	case DatumType::INTEGER:
		removeRecursively<int32_t>(mDatumVal.integerType);
		break;

	case DatumType::FLOAT:
		removeRecursively<float>(mDatumVal.floatingType);
		break;
		
	case DatumType::VECTOR:
		removeRecursively<vec4>(mDatumVal.vectorType);
		break;

	case DatumType::MATRIX:
		removeRecursively<mat4x4>(mDatumVal.matrixType);
		break;

	case DatumType::TABLE:
		removeRecursively<Scope*>(mDatumVal.tableType);
		break;

	case DatumType::STRING:
		removeRecursively<string>(mDatumVal.stringType);
		break;

	case DatumType::RTTI_POINTER:
		removeRecursively<RTTI*>(mDatumVal.rttiType);
		break;
	}
}

#pragma region SET_OVERLOADS

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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
		setSize(index + 1);
	}
	mDatumVal.matrixType[index] = value;
}

void Datum::set(Scope& value, uint32_t index)
{
	if ((mType != DatumType::UNKNOWN) && (mType != DatumType::TABLE))
	{
		throw runtime_error("The DatumType is already set to another type.");
	}
	if (mType == DatumType::UNKNOWN)
	{
		mType = DatumType::TABLE;
	}
	if (index >= mSize)
	{
		setSize(index + 1);
	}
	mDatumVal.tableType[index] = &value;
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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
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
		if (mIsExternal)
		{
			throw out_of_range("Invalid index.");
		}
		setSize(index + 1);
	}
	mDatumVal.rttiType[index] = value;
}

#pragma endregion

#pragma region SET_STORAGE_OVERLOADS

void Datum::setStorage(int32_t* externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::INTEGER);
	mSize = mCapacity = numberOfElements;
	mDatumVal.integerType = externalArray;
}

void Datum::setStorage(float* externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::FLOAT);
	mSize = mCapacity = numberOfElements;
	mDatumVal.floatingType = externalArray;
}

void Datum::setStorage(vec4* externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::VECTOR);
	mSize = mCapacity = numberOfElements;
	mDatumVal.vectorType = externalArray;
}

void Datum::setStorage(mat4x4* externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::MATRIX);
	mSize = mCapacity = numberOfElements;
	mDatumVal.matrixType = externalArray;
}

void Datum::setStorage(string* externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::STRING);
	mSize = mCapacity = numberOfElements;
	mDatumVal.stringType = externalArray;
}

void Datum::setStorage(RTTI** externalArray, uint32_t numberOfElements)
{
	emptyOut();
	mIsExternal = true;
	setType(DatumType::RTTI_POINTER);
	mSize = mCapacity = numberOfElements;
	mDatumVal.rttiType = externalArray;
}

#pragma endregion

void Datum::setFromString(string value, uint32_t index)
{
	switch (mType)
	{
	case DatumType::INTEGER:
	{
		set(stoi(value), index);
		break;
	}

	case DatumType::FLOAT:
	{
		set(stof(value), index);
		break;
	}

	case DatumType::VECTOR:
	{
		vec4 tempVector = stringToVector(value);
		set(tempVector, index);
		break;
	}

	case DatumType::MATRIX:
	{
		mat4x4 tempMatrix;
		char* input = const_cast<char*>(value.c_str());

		string vector0 = strtok(input, ")");
		string vector1 = strtok(nullptr, ")");
		string vector2 = strtok(nullptr, ")");
		string vector3 = strtok(nullptr, ")");

		tempMatrix[0] = stringToVector(vector0);
		tempMatrix[1] = stringToVector(vector1);
		tempMatrix[2] = stringToVector(vector2);
		tempMatrix[3] = stringToVector(vector3);

		set(tempMatrix, index);
		break;
	}

	case DatumType::STRING:
	{
		set(value, index);
		break;
	}

	default:
		throw runtime_error("Valid type not assigned.");
		break;
	}
}

string Datum::toString(uint32_t index)
{
	string temp;
	switch (mType)
	{
	case DatumType::INTEGER:
		temp = to_string(mDatumVal.integerType[index]);
		break;
	case DatumType::FLOAT:
		temp = to_string(mDatumVal.floatingType[index]);
		break;
	case DatumType::VECTOR:
		temp = to_string(mDatumVal.vectorType[index]);
		break;
	case DatumType::MATRIX:
		temp = to_string(mDatumVal.matrixType[index]);
		break;
	case DatumType::TABLE:
		temp = mDatumVal.tableType[index]->toString();
		break;
	case DatumType::STRING:
		temp = mDatumVal.stringType[index];
		break;
	case DatumType::RTTI_POINTER:
		temp = mDatumVal.rttiType[index]->toString();
		break;
	default:
		throw runtime_error("Type not set");
	}
	return temp;
}

Scope& Datum::operator[](std::uint32_t index)
{
	if (mType != DatumType::TABLE)
	{
		throw invalid_argument("Can't use this operator on this type.");
	}
	return *(get<Scope*>(index));
}

void Datum::emptyOut()
{
	clear();
	free(mDatumVal.genericType);
}

vec4 Datum::stringToVector(string vectorString)
{
	vec4 tempVector;
	char* input = const_cast<char*>(vectorString.c_str());

	//tokenize string and store the individual values of x, y, z, w as char*
	strtok(input, "(");
	string tempX = strtok(nullptr, "(,");
	string tempY = strtok(nullptr, ",");
	string tempZ = strtok(nullptr, ",");
	string tempW = strtok(nullptr, ")");

	//assign tokens to tempVector
	tempVector.x = stof(tempX);
	tempVector.y = stof(tempY);
	tempVector.z = stof(tempZ);
	tempVector.w = stof(tempW);

	return tempVector;
}

bool Datum::removeTable(const Scope* scope)
{
	bool removed = false;
	if (mType == DatumType::TABLE)
	{
		//Look for the scope and if found, memmove over it
		for (uint32_t i = 0; i < mSize; ++i)
		{
			if (mDatumVal.tableType[i] == scope)
			{
				memmove(mDatumVal.tableType[i], mDatumVal.tableType[i + 1], ((--mSize) - i) * sizeof(Scope*));
				removed = true;
				break;
			}
		}
	}
	return removed;
}

template <typename T>
void Datum::instantiateSize(T* datumVal, uint32_t size)
{
	while (mSize < size)
	{
		new(&datumVal[mSize++]) T();
	}
}

template <typename T>
void Datum::removeRecursively(T* datumVal, uint32_t size)
{
	while (mSize > size)
	{
		datumVal[--mSize].~T();
	}
}
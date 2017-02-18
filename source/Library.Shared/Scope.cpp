#include "pch.h"

#include "HashMap.h"
#include "Vector.h"
#include "Datum.h"
#include <string>
#include <cstdint>
#include "Scope.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Scope)

Scope::Scope(uint32_t size) :
	mParent(nullptr), mTable(size)
{
}

Scope::Scope(const Scope& obj):
	mParent(nullptr)
{
	for (Pair* value : obj.mOrder)
	{
		if (value->second.type() == DatumType::TABLE)
		{
			Scope& temp = appendScope(value->first);
			temp = *(value->second.get<Scope*>());
		}
		else
		{
			Datum& temp = append(value->first);
			temp = value->second;
		}
	}
}

Scope::~Scope()
{
	//orphan();
	clear();
}

Scope& Scope::operator=(const Scope& obj)
{
	if (this != &obj)
	{
		//orphan();
		clear();
		for (Pair* value : obj.mOrder)
		{
			if (value->second.type() == DatumType::TABLE)
			{
				Scope& temp = appendScope(value->first);
				temp = *(value->second.get<Scope*>());
			}
			else
			{
				Datum& temp = append(value->first);
				temp = value->second;
			}
		}
	}
	return *this;
}

bool Scope::operator==(const Scope& obj) const
{
	bool isEqual = true;
	if (mOrder.size() != obj.mOrder.size())
	{
		isEqual = false;
	}
	else
	{
		uint32_t size = mOrder.size();
		for (uint32_t index = 0; index < size; ++index )
		{
			if (mOrder[index] != mOrder[index])
			{
				isEqual = false;
				break;
			}
		}
	}

	return isEqual;
}

bool Scope::operator!=(const Scope& obj) const
{
	return !(*this == obj);
}

bool Scope::equals(const RTTI* obj) const
{
	Scope* temp = obj->as<Scope>();
	if (temp != nullptr)
	{
		return (*this == *temp);
	}
	return false;
}

Datum& Scope::operator[](const string& name)
{
	return append(name);
}

Datum& Scope::operator[](uint32_t index)
{
	return mOrder[index]->second;
}

void Scope::clear()
{
	for (Pair* pair : mOrder)
	{
		if (pair->second.type() == DatumType::TABLE)
		{
			delete pair->second.get<Scope*>();
		}
	}
	mOrder.clear();
	mTable.clear();
}

Datum& Scope::append(const std::string& name)
{
	if (name == "")
	{
		throw runtime_error("Can't append using empty string.");
	}

	bool inserted;
	Datum temp;
	TableIterator tableIt = mTable.insert(Pair(name, temp), inserted);
	if (inserted)
	{
		mOrder.pushBack(&(*tableIt));
	}

	return mTable[name];
}

Scope& Scope::appendScope(const std::string& name)
{
	Datum* scope = &append(name);
	Scope* returnVal = new Scope;
	returnVal->mParent = this;

	//set the value of the Scope.
	scope->set(returnVal);
	return *returnVal;
}

Scope& Scope::getParent()
{
	return *mParent;
}

const Scope& Scope::getParent() const
{
	return *mParent;
}

Datum* Scope::find(const string& name) const
{
	TableIterator found = mTable.find(name);
	if (found == mTable.end())
	{
		return nullptr;
	}
	return &(found->second);
}

Datum* Scope::search(const string& name, Scope** scope)
{
	*scope = nullptr;
	Datum* found = find(name);
	if (found)
	{
		*scope = this;
		return found;
	}
	else if(mParent != nullptr)
	{
		mParent->search(name, scope);
	}
	else
	{
		return nullptr;
	}
}
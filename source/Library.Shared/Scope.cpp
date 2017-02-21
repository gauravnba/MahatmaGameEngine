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
	clear();
}

Scope& Scope::operator=(const Scope& obj)
{
	if (this != &obj)
	{
		clear();
		for (Pair* value : obj.mOrder)
		{
			if (value->second.type() == DatumType::TABLE)
			{
				uint32_t size = value->second.size();
				for (uint32_t i = 0; i < size; ++i)
				{
					Scope& temp = appendScope(value->first);
					temp = *(value->second.get<Scope*>(i));
				}
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
			if (*(mOrder[index]) != *(obj.mOrder[index]))
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
	if (obj != nullptr)
	{
		Scope* temp = obj->as<Scope>();
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
			uint32_t index = pair->second.size();
			for (;index > 0; --index)
			{
				Scope* tempScope = pair->second.get<Scope*>(index - 1);
				tempScope->orphan();
				delete tempScope;
			}
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
	Datum* scopeDatum = &append(name);
	if (scopeDatum->type() != DatumType::TABLE)
	{
		if (scopeDatum->type() != DatumType::UNKNOWN)
		{
			throw invalid_argument("Name exists but is not of type scope.");
		}
	}

	Scope* returnVal = new Scope;
	returnVal->mParent = this;

	//Append scope to the Datum array
	scopeDatum->set(returnVal, scopeDatum->size());
	return *returnVal;
}

Scope* Scope::getParent()
{
	return mParent;
}

Scope* const Scope::getParent() const
{
	return mParent;
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
	}
	else if(mParent != nullptr)
	{
		found = mParent->search(name, scope);
	}

	return found;
}

void Scope::adopt(Scope* child, const std::string& name)
{
	//Reset parent of the child Scope to this
	child->orphan();
	child->mParent = this;

	//Append the child to this.
	Datum* temp = &append(name);
	temp->set(child);
}

void Scope::orphan()
{
	if (mParent != nullptr)
	{
		for (Pair* pair : mParent->mOrder)
		{
			if (pair->second.removeTable(this))
			{
				mParent = nullptr;
				break;
			}
		}
	}
}

string Scope::toString() const
{
	return "Scope";
}
#include "pch.h"

#include "Attributed.h"

using namespace MahatmaGameEngine;
using namespace std;
using namespace glm;

RTTI_DEFINITIONS(Attributed)

HashMap<uint64_t, Vector<string>> Attributed::mPrescribedAttributes;

Attributed::Attributed()
{
}

Attributed::Attributed(const Attributed& obj) :
	Scope(obj)
{
	(*this)["this"] = this;
}

Attributed::Attributed(Attributed&& obj) :
	Scope(move(obj))
{
	(*this)["this"] = this;
}

Attributed::~Attributed()
{
}

Attributed& Attributed::operator=(const Attributed& obj)
{
	if (this != &obj)
	{
		Scope::operator=(obj);
		(*this)["this"] = this;
	}
	return *this;
}

Attributed& Attributed::operator=(Attributed&& obj)
{
	if (this != &obj)
	{
		Scope::operator=(move(obj));
		(*this)["this"] = this;
	}
	return *this;
}

bool Attributed::isAttribute(const string& name) const
{
	bool found = false;
	if (find(name) != nullptr)
	{
		found = true;
	}
	return found;
}

bool Attributed::isPrescribedAttribute(const string& name) const
{
	bool isPrescribed = false;
	Vector<string>& attributesList = mPrescribedAttributes[typeIdInstance()];
	if (isAttribute(name) && (attributesList.find(name) != attributesList.end()))
	{
		isPrescribed = true;
	}
	return isPrescribed;
}

bool Attributed::isAuxiliaryAttribute(const string& name) const
{
	return (isAttribute(name) && !isPrescribedAttribute(name));
}

Datum& Attributed::appendAuxiliaryAttribute(const string& name)
{
	if (!isPrescribedAttribute(name))
	{
		return append(name);
	}
	else
	{
		throw runtime_error("Is already a prescribed attribute.");
	}
}

void Attributed::copyAuxiliaryAttributes(const Attributed& obj)
{
	//Copy all the auxiliary attributes from message to this scope.
	for (uint32_t i = 0; i < obj.size(); ++i)
	{
		auto& pair = obj.getPair(i);
		if (obj.isAuxiliaryAttribute(pair.first))
		{
			(*this)[pair.first] = pair.second;
		}
	}
}

uint32_t Attributed::auxiliaryBegin() const
{
	return mPrescribedAttributes[typeIdInstance()].size();
}

Datum& Attributed::addNestedScope(const string& name, Scope& scope)
{
	Datum& temp = append(name);
	adopt(&scope, name);
	return temp;
}

#pragma region APPEND_INTERNAL_ATTRIBUTE
Datum& Attributed::appendInternalAttribute(const string& name, int32_t value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}

Datum& Attributed::appendInternalAttribute(const string& name, float value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}

Datum& Attributed::appendInternalAttribute(const string& name, vec4 value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}

Datum& Attributed::appendInternalAttribute(const string& name, mat4x4 value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}

Datum& Attributed::appendInternalAttribute(const string& name, string value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}

Datum& Attributed::appendInternalAttribute(const string& name, RTTI* value, uint32_t numberOfElements)
{
	return addInternalAttribute(name, value, numberOfElements);
}
#pragma endregion

#pragma region APPEND_EXTERNAL_ATTRIBUTE
Datum& Attributed::appendExternalAttribute(const std::string& name, int32_t* attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

Datum& Attributed::appendExternalAttribute(const std::string& name, float* attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

Datum& Attributed::appendExternalAttribute(const std::string& name, vec4* attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

Datum& Attributed::appendExternalAttribute(const std::string& name, mat4x4* attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

Datum& Attributed::appendExternalAttribute(const std::string& name, string* attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

Datum& Attributed::appendExternalAttribute(const std::string& name, RTTI** attribute, std::uint32_t numberOfElements /* = 1 */)
{
	return addExternalAttribute(name, attribute, numberOfElements);
}

#pragma endregion

void Attributed::setTheThisAttribute()
{
	(*this)["this"] = this;
	addToPrescribed("this");
}

void Attributed::addToPrescribed(const string& name)
{
	Vector<string>& temp = mPrescribedAttributes[typeIdInstance()];
	if (temp.find(name) == temp.end())
	{
		temp.pushBack(name);
	}
}

template <typename T>
Datum& Attributed::addInternalAttribute(const string& name, T value, uint32_t numberOfElements)
{
	Datum& temp = append(name);
	for (uint32_t i = 0; i < numberOfElements; ++i)
	{
		temp.set(value, i);
	}
	return temp;
}

template <typename T>
Datum& Attributed::addExternalAttribute(const string& name, T* attribute, uint32_t numberOfElements)
{
	Datum& temp = append(name);
	temp.setStorage(attribute, numberOfElements);
	return temp;
}
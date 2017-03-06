#include "pch.h"

#include "Attributed.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Attributed)

Attributed::Attributed() :
	mAuxiliaryBegin(0)
{
	Vector<string> temp;
	temp.pushBack(typeName());
	mPrescribedAttributes.insert(PrescribedAttributesPair(typeIdClass(), temp));
	++mAuxiliaryBegin;
}

Attributed::Attributed(const Attributed& obj) :
	mAuxiliaryBegin(obj.mAuxiliaryBegin)
{
	mPrescribedAttributes = obj.mPrescribedAttributes;
}

Attributed::Attributed(Attributed&& obj) :
	mAuxiliaryBegin(obj.mAuxiliaryBegin)
{
	mPrescribedAttributes = move(obj.mPrescribedAttributes);

	obj.mAuxiliaryBegin = 0;
}

Attributed::~Attributed()
{
}

Attributed& Attributed::operator=(const Attributed& obj)
{
	if (this != &obj)
	{
		mPrescribedAttributes = obj.mPrescribedAttributes;
		mAuxiliaryBegin = obj.mAuxiliaryBegin;
	}
	return *this;
}

Attributed& Attributed::operator=(Attributed&& obj)
{
	if (this != &obj)
	{
		mPrescribedAttributes = move(obj.mPrescribedAttributes);
		mAuxiliaryBegin = obj.mAuxiliaryBegin;

		obj.mAuxiliaryBegin = 0;
	}
	return *this;
}

bool Attributed::isAttribute(const string& name)
{
	bool found = false;
	if (find(name) != nullptr)
	{
		found = true;
	}
	return found;
}

bool Attributed::isPrescribedAttribute(const string& name)
{
	bool isPrescribed = false;
	Vector<string> attributesList = mPrescribedAttributes[typeIdClass()];
	if (isAttribute(name) && (attributesList.find(name) != attributesList.end()))
	{
		isPrescribed = true;
	}
	return isPrescribed;
}

bool Attributed::isAuxiliaryAttribute(const string& name)
{
	return !(isPrescribedAttribute(name));
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

Datum& Attributed::appendInternalAttribute(const string& name)
{
	return append(name);
}
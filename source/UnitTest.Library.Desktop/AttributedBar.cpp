#include "pch.h"

#include "AttributedBar.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;
using namespace glm;
using namespace std;

RTTI_DEFINITIONS(AttributedBar)

AttributedBar::AttributedBar()
{
	setTheThisAttribute();

	initializeMembers();
	mDerivedScope = new Scope;

	appendExternalAttribute("DerivedInteger", mDerivedExtInteger, numElements);
	addToPrescribed("DerivedInteger");
	appendExternalAttribute("DerivedMatrix", mDerivedExtMatrix, numElements);
	addToPrescribed("DerivedMatrix");
	addNestedScope("DerivedTable", *mDerivedScope);
	addToPrescribed("DerivedTable");

	appendInternalAttribute("DerivedInternalInteger", mDerivedIntInteger);
	addToPrescribed("DerivedInternalInteger");
	appendInternalAttribute("DerivedInternalMatrix", mDerivedIntMatrix);
	addToPrescribed("DerivedInternalMatrix");
}

AttributedBar::AttributedBar(const AttributedBar& obj) :
	AttributedFoo(obj)
{
	fixUpDatums();
}

AttributedBar::AttributedBar(AttributedBar&& obj) :
	AttributedFoo(move(obj))
{
}

AttributedBar& AttributedBar::operator=(const AttributedBar& obj)
{
	if (this != &obj)
	{
		AttributedFoo::operator=(obj);
		fixUpDatums();
	}
	return *this;
}

AttributedBar& AttributedBar::operator=(AttributedBar&& obj)
{
	if (this != &obj)
	{
		AttributedFoo::operator=(move(obj));
	}
	return *this;
}

AttributedBar::~AttributedBar()
{
}

void AttributedBar::fixUpDatums()
{
	initializeMembers();

	(*this)["DerivedInteger"].setStorage(mDerivedExtInteger, numElements);
	(*this)["DerivedMatrix"].setStorage(mDerivedExtMatrix, numElements);
	mDerivedScope = (*this)["Table"].get<Scope*>();
}

void AttributedBar::initializeMembers()
{
	int32_t iA = 10;
	int32_t iB = 20;
	float fA = 10.5f;
	float fB = 20.5f;
	float fC = 30.5f;
	float fD = 40.5f;
	vec4 vA = vec4(vec3(fA), fB);
	vec4 vB = vec4(vec3(fB), fA);
	vec4 vC = vec4(vec3(fC), fD);
	vec4 vD = vec4(vec3(fD), fC);
	mat4x4 mA = mat4x4(vA, vB, vC, vD);
	mat4x4 mB = mat4x4(vB, vC, vD, vA);
	string sA = "test";

	mDerivedExtInteger[0] = iA;
	mDerivedExtMatrix[0] = mA;

	mDerivedIntInteger = iB;
	mDerivedIntMatrix = mB;
}
#include "pch.h"

#include "AttributedFoo.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;
using namespace glm;
using namespace std;

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo()
{
	initializeSignature();

	initializeMembers();
	mScope = new Scope;

	appendExternalAttribute("Integer", mIntAttribute, numElements);
	addToPrescribed("Integer");
	appendExternalAttribute("FloatingPoint", mFloatAttribute, numElements);
	addToPrescribed("FloatingPoint");
	appendExternalAttribute("Vector", mVectorAttribute, numElements);
	addToPrescribed("Vector");
	appendExternalAttribute("Matrix", mMatrixAttribute, numElements);
	addToPrescribed("Matrix");
	appendExternalAttribute("String", mStringAttribute, numElements);
	addToPrescribed("String");
	addNestedScope("Table", *mScope);
	addToPrescribed("Table");
	appendExternalAttribute("RTTI", mRTTI, numElements);
	addToPrescribed("RTTI");

	appendInternalAttribute("InternalInteger", mInternalInt);
	appendInternalAttribute("InternalFloat", mInternalFloat);
	appendInternalAttribute("InternalVector", mInternalVector);
	appendInternalAttribute("InternalMatrix", mInternalMatrix);
	appendInternalAttribute("InternalString", mInternalString);
}

AttributedFoo::AttributedFoo(const AttributedFoo& obj)
	:Attributed(obj)
{
	mFoo = obj.mFoo;
	fixUpDatums();
}

AttributedFoo::AttributedFoo(AttributedFoo&& obj) :
	Attributed(move(obj))
{
}

AttributedFoo& AttributedFoo::operator=(const AttributedFoo& obj)
{
	if (this != &obj)
	{
		Attributed::operator=(obj);
		mFoo = obj.mFoo;
		fixUpDatums();
	}
	return *this;
}

AttributedFoo& AttributedFoo::operator=(AttributedFoo&& obj)
{
	if (this != &obj)
	{
		Attributed::operator=(move(obj));
	}
	return *this;
}

AttributedFoo::~AttributedFoo()
{
}

void AttributedFoo::fixUpDatums()
{
	initializeMembers();

	(*this)["Integer"].setStorage(mIntAttribute, 1);
	(*this)["FloatingPoint"].setStorage(mFloatAttribute, 1);
	(*this)["Vector"].setStorage(mVectorAttribute, 1);
	(*this)["Matrix"].setStorage(mMatrixAttribute, 1);
	(*this)["String"].setStorage(mStringAttribute, 1);
	mScope = (*this)["Table"].get<Scope*>();
	(*this)["RTTI"].set(mRTTI[0]);
}

void AttributedFoo::initializeMembers()
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
	string sB = "test1";

	mIntAttribute[0] = iA;
	mFloatAttribute[0] = fA;
	mVectorAttribute[0] = vA;
	mMatrixAttribute[0] = mA;
	mStringAttribute[0] = sA;
	mFoo = Foo(30);
	mRTTI[0] = &mFoo;

	mInternalInt = iB;
	mInternalFloat = fB;
	mInternalVector = vB;
	mInternalMatrix = mB;
	mInternalString = sB;
}

Datum& AttributedFoo::appendExistingScope(const string& name, Scope& scope)
{
	return addNestedScope(name, scope);
}
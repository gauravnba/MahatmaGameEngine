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
	addNestedScope("Table", mScope);
	addToPrescribed("Table");
}

AttributedFoo::AttributedFoo(const AttributedFoo& obj)
	:Attributed(obj)
{
	fixUpDatums();
}

AttributedFoo::AttributedFoo(AttributedFoo&& obj) :
	Attributed(move(obj))
{
}

AttributedFoo& AttributedFoo::operator=(const AttributedFoo& obj)
{
	AttributedFoo& temp = *(Attributed::operator=(obj)).as<AttributedFoo>();
	fixUpDatums();
	return temp;
}

AttributedFoo& AttributedFoo::operator=(AttributedFoo&& obj)
{
	AttributedFoo& temp = *(Attributed::operator=(move(obj))).as<AttributedFoo>();
	fixUpDatums();
	return temp;
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
}

void AttributedFoo::initializeMembers()
{
	int32_t iA = 10;
	float fA = 10.5f;
	float fB = 20.5f;
	float fC = 30.5f;
	float fD = 40.5f;
	vec4 vA = vec4(vec3(fA), fB);
	vec4 vB = vec4(vec3(fB), fA);
	vec4 vC = vec4(vec3(fC), fD);
	vec4 vD = vec4(vec3(fD), fC);
	mat4x4 mA = mat4x4(vA, vB, vC, vD);
	string sA = "test";

	mIntAttribute[0] = iA;
	mFloatAttribute[0] = fA;
	mVectorAttribute[0] = vA;
	mMatrixAttribute[0] = mA;
	mStringAttribute[0] = sA;
}
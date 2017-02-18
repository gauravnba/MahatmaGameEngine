#include "pch.h"

#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace glm;
	using namespace std;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(ScopeTest)
	{
	private:
#define SCOPE_TEST_DATA_DECLARATION											\
		string intType = "integer";											\
		int32_t iA = 10;													\
																			\
		string floatType = "float";											\
		float fA = 10.5f;													\
		float fB = 20.5f;													\
		float fC = 30.5f;													\
		float fD = 40.5f;													\
																			\
		string vecType = "vector";											\
		vec4 vA = vec4(vec3(fA), fB);										\
		vec4 vB = vec4(vec3(fB), fA);										\
		vec4 vC = vec4(vec3(fC), fD);										\
		vec4 vD = vec4(vec3(fD), fC);										\
																			\
		string matrixType = "matrix";										\
		mat4x4 mA = mat4x4(vA, vB, vC, vD);									\
		mat4x4 mB = mat4x4(vB, vC, vD, vA);									\
		mat4x4 mC = mat4x4(vC, vD, vA, vB);									\
		mat4x4 mD = mat4x4(vD, vA, vB, vC);									\
																			\
		string stringType = "string";										\
		string sA = "test";													\
		string sB = "anotherTest";											\
																			\
		string tableType = "table";											\
		Scope childScope;													\

		//Require SCOPE_TEST_DATA_DECLARATION before it
#define POPULATE_TEST_SCOPE													\
		Scope testScope;													\
		Datum integer = testScope.append(intType);							\
		integer.set(iA);													\
		Datum floatingPoint = testScope.append(floatType);					\
		floatingPoint.set(fA);												\
		floatingPoint.set(fB);												\
		Datum vector4 = testScope.append(vecType);							\
		vector4.set(vA);													\
		vector4.set(vB);													\
		Datum matrix4x4 = testScope.append(matrixType);						\
		matrix4x4.set(mA);													\
		matrix4x4.set(mB);													\
		Datum stringDatum = testScope.append(stringType);					\
		stringDatum.set(sA);												\
		stringDatum.set(sB);												\
		Scope childTable = testScope.appendScope(tableType);				\


	public:
		//This method sets up the initial memory state to check for memory leaks.
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		//This test method checks the current memory state against the initial state to check for memory leaks.
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(appendTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			Scope testScope;
			Datum* test = &testScope.append("test");
			test->set(iA);

			Assert::IsTrue(testScope["test"] == *test);
			Assert::IsTrue(testScope[0] == testScope["test"]);
		}

		TEST_METHOD(copyConstructorTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			POPULATE_TEST_SCOPE

			Scope cloneScope = testScope;

			Assert::IsTrue(cloneScope == testScope);
			Assert::IsFalse(cloneScope != testScope);
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			SCOPE_TEST_DATA_DECLARATION
			POPULATE_TEST_SCOPE

			Scope newScope;
			newScope = testScope;

			Assert::IsTrue(newScope == testScope);
		}

		TEST_METHOD(appendScopeTest)
		{
			int32_t iA = 10;
			string intType = "integer";
			float fA = 10.05f;
			string floatType = "float";

			string tableType = "Scope";
			Scope testScope;
			Scope childScope = testScope.appendScope(tableType);

			Datum integer = childScope.append(intType);
			integer = iA;

			Datum floating = childScope.append(floatType);
			floating = fA;
		}

		TEST_METHOD(equalsOverrideTest)
		{
			SCOPE_TEST_DATA_DECLARATION;
			POPULATE_TEST_SCOPE;

			Scope newScope;
			newScope = testScope;
			Scope* scopePointer = &testScope;
			Assert::IsTrue(newScope.equals(scopePointer));
		}

		TEST_METHOD(scopeFindTest)
		{

		}

		TEST_METHOD(scopeSearchTest)
		{

		}

	private:																			
		static _CrtMemState sStartMemState;									

	};

	_CrtMemState ScopeTest::sStartMemState;
}
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

			auto emptyStringException = [&testScope]{testScope.append("");};
			Assert::ExpectException<exception>(emptyStringException);

			Assert::IsTrue(testScope["test"] == *test);
			Assert::IsTrue(testScope[0] == testScope["test"]);
		}

		TEST_METHOD(copyConstructorTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			POPULATE_TEST_SCOPE

			Scope cloneScope = testScope;

			Assert::IsTrue(cloneScope == testScope);

			Datum* test = &(childTable->append("test"));
			test->set(iA);

			Assert::IsTrue(cloneScope != testScope);
			Assert::IsTrue(cloneScope[intType] == testScope[intType]);
			Assert::IsTrue(cloneScope[tableType].get<int32_t>() != testScope[tableType].get<int32_t>());
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			SCOPE_TEST_DATA_DECLARATION
			POPULATE_TEST_SCOPE

			Scope newScope;
			newScope = testScope;

			Assert::IsTrue(newScope == testScope);

			Datum* test = &(childTable->append("test"));
			test->set(iA);

			Assert::IsTrue(newScope != testScope);
			Assert::IsTrue(newScope[intType] == testScope[intType]);
			Assert::IsTrue(newScope[tableType].get<int32_t>() != testScope[tableType].get<int32_t>());
		}

		TEST_METHOD(moveSemanticsTest)
		{
			SCOPE_TEST_DATA_DECLARATION
			POPULATE_TEST_SCOPE

			Scope newScope = move(testScope);

			Assert::IsTrue(newScope != testScope);
			Assert::IsTrue(childTable->getParent() != &testScope);
			Assert::IsTrue(childTable->getParent() == &newScope);

			Datum* test = &(childTable->append("test"));
			test->set(iA);

			testScope = move(newScope);

			Assert::IsTrue(newScope != testScope);
			Assert::IsTrue(testScope[tableType] == childTable);
			Assert::IsTrue(childTable->getParent() != &newScope);
			Assert::IsTrue(childTable->getParent() == &testScope);

			//Test parenting of move scope.
			Scope newChild = move(*childTable);

			Assert::IsTrue(newChild != *childTable);
			Assert::IsTrue(newChild.getParent() == &testScope);
			Assert::IsNull(childTable->getParent());

			*childTable = move(newChild);

			Assert::IsTrue(newChild != *childTable);
			Assert::IsTrue(childTable->getParent() == &testScope);
			Assert::IsNull(newChild.getParent());
		}

		TEST_METHOD(appendScopeTest)
		{
			int32_t iA = 10;
			string intType = "integer";
			float fA = 10.05f;
			string floatType = "float";
			string vecType = "vector";

			string tableType = "Scope";
			Scope testScope;
			Scope* childScope = &testScope.appendScope(tableType);

			Datum* integer = &childScope->append(intType);
			*integer = iA;

			Datum* floating = &childScope->append(floatType);
			*floating = fA;

			auto nonScopeNameException = [&childScope, &floatType] {childScope->appendScope(floatType); };
			Assert::ExpectException<exception>(nonScopeNameException);

			string grandChild = "Pota";

			Scope* childOfChild = &(childScope->appendScope(grandChild));
			childOfChild->append(vecType);

			Assert::IsTrue(childOfChild == childScope->operator[](grandChild).get<Scope*>());
		}

		TEST_METHOD(equalsOverrideTest)
		{
			SCOPE_TEST_DATA_DECLARATION
			POPULATE_TEST_SCOPE

			UNREFERENCED_PARAMETER(childTable);

			Scope* nullScope = nullptr;
			Scope newScope = testScope;
			Assert::IsTrue(newScope.equals(&testScope));

			Scope inequalScope;												
			inequalScope.append(intType);													
			inequalScope.append(floatType);									
			inequalScope.append(vecType);									
			inequalScope.append(matrixType);
			inequalScope.append(stringType);										
			inequalScope.appendScope(tableType);

			Assert::IsFalse(newScope.equals(&inequalScope));
			inequalScope.append("test");
			Assert::IsFalse(newScope.equals(&inequalScope));
			Assert::IsFalse(newScope.equals(nullScope));
		}

		TEST_METHOD(scopeFindTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			POPULATE_TEST_SCOPE

			Datum* test = &(childTable->append("test"));
			test->set(iA);

			Assert::IsTrue(testScope.find(intType) == integer);
			Assert::IsTrue(testScope.find(intType) != nullptr);

			Datum* foundDatum = testScope.find(intType);

			Assert::IsTrue(testScope[intType] == *foundDatum);
			Assert::IsTrue(testScope.find("notFound") == nullptr);
			Assert::IsTrue(testScope.find("test") == nullptr);
		}

		TEST_METHOD(scopeSearchTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			POPULATE_TEST_SCOPE

			string searchTest = "searchTest";

			Datum* testDatum = &(testScope.append("searchTest"));
			Scope* foundScope;

			Assert::IsTrue(testScope.search(searchTest, &foundScope) == testDatum);
			Assert::IsTrue(childTable->search(searchTest, &foundScope) == testDatum);
			Assert::IsTrue(childTable->search("testNotFound", &foundScope) == nullptr);
		}

		TEST_METHOD(getParentTest)
		{
			Scope testScope;
			string child = "childTable";
			Scope* childScope = &(testScope.appendScope(child));
			Assert::IsTrue(childScope->getParent() == &testScope);
			Assert::IsTrue(testScope.getParent() == nullptr);

			string constChild = "constChild";
			const Scope* constChildScope = &(testScope.appendScope(constChild));
			Assert::IsTrue(constChildScope->getParent() == &testScope);
		}

		TEST_METHOD(rttiTests)
		{
			Scope testScope;
			uint64_t typeID = testScope.typeIdClass();

			Assert::IsTrue(testScope.is(typeID));
			Assert::IsTrue(testScope.is("Scope"));
			Assert::AreEqual(testScope.typeIdClass(), testScope.typeIdInstance());
			Assert::IsNotNull(testScope.queryInterface(typeID));

			RTTI* testRTTI = dynamic_cast<RTTI*>(&testScope);
			Assert::IsNotNull(testRTTI->queryInterface(typeID));
			Assert::IsTrue(testRTTI->is(typeID));
			Assert::IsTrue(testRTTI->is("Scope"));
			Assert::AreEqual(testRTTI->toString(), string("Scope"));
			Assert::IsTrue(testRTTI->equals(&testScope));
		}

		TEST_METHOD(scopeAdoptTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			POPULATE_TEST_SCOPE

			Scope newScope;
			string newChildName = "newChild";
			Assert::IsTrue(childTable->getParent() == &testScope);
			newScope.adopt(childTable, newChildName);
			Assert::IsTrue(childTable->getParent() == &newScope);
		}

	private:																			
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}
#include "pch.h"

#include "Attributed.h"
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace glm;
	using namespace std;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_CLASS_INITIALIZE(AttributedTestInitialize)
		{
			AttributedFoo tempFoo;
		}

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

		TEST_METHOD(copyConstructorTest)
		{
			AttributedFoo foo1;

			AttributedFoo foo2 = foo1;

			Assert::IsTrue(foo1.isAttribute("Integer"));
			Assert::IsTrue(foo2.isAttribute("Integer"));
			Assert::IsTrue(foo2.isPrescribedAttribute("Integer"));
			Assert::AreEqual(foo1.auxiliaryBegin(), foo2.auxiliaryBegin());
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			AttributedFoo foo1;
			Assert::IsTrue(foo1.isPrescribedAttribute("this"));

			AttributedFoo foo2;
			foo2.appendAuxiliaryAttribute("Auxiliary");
			Assert::IsTrue(foo2.isAuxiliaryAttribute("Auxiliary"));
			foo2 = foo1;

			Assert::IsTrue(foo1.isAttribute("Integer"));
			Assert::IsTrue(foo2.isAttribute("Integer"));
			Assert::IsTrue(foo2.isPrescribedAttribute("Integer"));
			Assert::IsFalse(foo2.isAuxiliaryAttribute("Auxiliary"));
			Assert::AreEqual(foo1.auxiliaryBegin(), foo2.auxiliaryBegin());
		}

		TEST_METHOD(moveConstructorTest)
		{
			AttributedFoo* foo1 = new AttributedFoo;
			foo1->appendAuxiliaryAttribute("Auxiliary1");
			Assert::IsTrue(foo1->isAuxiliaryAttribute("Auxiliary1"));
			AttributedFoo foo2 = move(*foo1);
			delete foo1;
			Assert::IsTrue(foo2.isAuxiliaryAttribute("Auxiliary1"));
			Assert::IsTrue(foo2.isPrescribedAttribute("Integer"));
			Assert::IsTrue(foo2.isPrescribedAttribute("this"));
		}

		TEST_METHOD(moveAssignmentOperatorTest)
		{

		}

		TEST_METHOD(isAttributeTest)
		{

		}

		TEST_METHOD(isPrescribedAttributeTest)
		{

		}

		TEST_METHOD(isAuxiliaryAttributeTest)
		{

		}

		TEST_METHOD(appendAuxiliaryAttributeTest)
		{
			AttributedFoo foo1;
			foo1.appendAuxiliaryAttribute("Auxiliary");
			Assert::IsTrue(foo1.isAuxiliaryAttribute("Auxiliary"));
			
			auto appendAuxiliaryAsPrescribedException = [&foo1] {foo1.appendAuxiliaryAttribute("Integer"); };
			Assert::ExpectException<exception>(appendAuxiliaryAsPrescribedException);
		}

		TEST_METHOD(auxiliaryBeginTest)
		{
			AttributedFoo foo;
			Assert::AreEqual(foo.auxiliaryBegin(), 5U);
		}

		TEST_METHOD(appendInternalAttributeTest)
		{

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}
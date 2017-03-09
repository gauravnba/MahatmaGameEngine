#include "pch.h"

#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"

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
			AttributedBar tempBar;
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
			AttributedFoo* foo1 = new AttributedFoo;
			foo1->appendAuxiliaryAttribute("Auxiliary1");
			Assert::IsTrue(foo1->isAuxiliaryAttribute("Auxiliary1"));
			AttributedFoo foo2;
			foo2.appendAuxiliaryAttribute("Temp");
			foo2 = move(*foo1);
			delete foo1;
			Assert::IsTrue(foo2.isAuxiliaryAttribute("Auxiliary1"));
			Assert::IsFalse(foo2.isAuxiliaryAttribute("Temp"));
			Assert::IsTrue(foo2.isPrescribedAttribute("Integer"));
			Assert::IsTrue(foo2.isPrescribedAttribute("this"));
		}

		TEST_METHOD(isAttributeTest)
		{
			AttributedFoo foo1;

			Assert::IsTrue(foo1.isAttribute("this"));
			Assert::IsFalse(foo1.isAttribute("Temp"));
		}

		TEST_METHOD(isPrescribedAttributeTest)
		{
			AttributedFoo foo1;
			foo1.appendAuxiliaryAttribute("Auxiliary");

			Assert::IsTrue(foo1.isPrescribedAttribute("this"));
			Assert::IsFalse(foo1.isPrescribedAttribute("Auxiliary"));
			Assert::IsFalse(foo1.isPrescribedAttribute("Temp"));
		}

		TEST_METHOD(isAuxiliaryAttributeTest)
		{
			AttributedFoo foo1;
			foo1.appendAuxiliaryAttribute("Auxiliary");

			Assert::IsFalse(foo1.isAuxiliaryAttribute("this"));
			Assert::IsTrue(foo1.isAuxiliaryAttribute("Auxiliary"));
			Assert::IsFalse(foo1.isAuxiliaryAttribute("Temp"));
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
			Assert::AreEqual(foo.auxiliaryBegin(), 14U);
		}

		TEST_METHOD(addNestedScopeTest)
		{
			AttributedFoo foo;

			Scope* scope = new Scope;
			scope->append("Temp");

			Datum& tempDatum = foo.appendExistingScope("TableTest", *scope);
			Assert::IsTrue(*(tempDatum.get<Scope*>()) == *scope);
		}

		/************************************************************ Derived Class Tests ******************************************************************/
		TEST_METHOD(derivedCopyConstructorTest)
		{
			AttributedBar bar1;
			bar1.appendAuxiliaryAttribute("Temp");
			Assert::IsTrue(bar1.isAuxiliaryAttribute("Temp"));

			AttributedBar bar2 = bar1;
			Assert::IsTrue(bar2.isAuxiliaryAttribute("Temp"));
			Assert::IsTrue(bar2.isPrescribedAttribute("DerivedInteger"));
		}

		TEST_METHOD(derivedAssignmentOperatorTest)
		{
			AttributedBar bar1;
			bar1.appendAuxiliaryAttribute("Temp");
			Assert::IsTrue(bar1.isAuxiliaryAttribute("Temp"));

			AttributedBar bar2;
			bar2.appendAuxiliaryAttribute("Temp1");
			bar2 = bar1;
			Assert::IsFalse(bar2.isAuxiliaryAttribute("Temp1"));
			Assert::IsTrue(bar2.isAuxiliaryAttribute("Temp"));
			Assert::IsTrue(bar2.isPrescribedAttribute("DerivedInteger"));
		}

		TEST_METHOD(derivedMoveConstructorTest)
		{
			AttributedBar* bar1 = new AttributedBar;
			bar1->appendAuxiliaryAttribute("Temp");
			Assert::IsTrue(bar1->isAuxiliaryAttribute("Temp"));

			AttributedBar bar2 = move(*bar1);
			delete bar1;
			Assert::IsTrue(bar2.isAuxiliaryAttribute("Temp"));
			Assert::IsTrue(bar2.isPrescribedAttribute("DerivedInteger"));
		}

		TEST_METHOD(derivedMoveAssignmentTest)
		{
			AttributedBar* bar1 = new AttributedBar;
			bar1->appendAuxiliaryAttribute("Temp");
			Assert::IsTrue(bar1->isAuxiliaryAttribute("Temp"));

			AttributedBar bar2;
			bar2 = move(*bar1);
			delete bar1;
			Assert::IsTrue(bar2.isAuxiliaryAttribute("Temp"));
			Assert::IsTrue(bar2.isPrescribedAttribute("DerivedInteger"));
		}

		TEST_METHOD(derivedAppendAuxiliaryAttributeTest)
		{
			AttributedBar bar;
			Assert::IsFalse(bar.isAttribute("Temp"));

			Datum& temp = bar.appendAuxiliaryAttribute("Temp");
			temp.set(10);
			Assert::IsTrue(bar.isAuxiliaryAttribute("Temp"));
			Assert::IsFalse(bar.isPrescribedAttribute("Temp"));
			Assert::IsTrue(temp == bar["Temp"]);
		}

		TEST_METHOD(derivedAuxiliaryBeginTest)
		{
			AttributedBar bar;
			Assert::AreEqual(bar.auxiliaryBegin(), 6U);
			bar.appendAuxiliaryAttribute("Temp");
			Assert::AreEqual(bar.auxiliaryBegin(), 6U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}
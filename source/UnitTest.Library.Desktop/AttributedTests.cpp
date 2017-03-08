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
			Assert::AreEqual(foo1.auxiliaryBegin(), foo2.auxiliaryBegin());
		}

		TEST_METHOD(assignmentOperatorTest)
		{

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}
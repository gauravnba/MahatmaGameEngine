#include "CppUnitTest.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SampleTest)
	{
	public:
		//This method sets up the initial memory state to check for memory leaks.
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		//This is a sample test to check if the Unit Test configuration is properly set up.
		TEST_METHOD(SListTest)
		{
			int data = 10;
			SList* sList = new SList(data);
			
			Assert::AreEqual(data, sList->getData());

			delete sList;
		}

		//This test method checks the current memory state against the initial state to check for memory leaks.
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
#endif
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SampleTest::sStartMemState;

}
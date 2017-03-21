#include "pch.h"

#include "XMLParseMaster.h"
#include "XMLParseHelperMotorcycle.h"
#include "SharedDataMotorcycles.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(XMLParseMasterTest)
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

		TEST_METHOD(constructorTest)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			XMLParseMaster xmlTest(sharedData);

			Assert::AreEqual(reinterpret_cast<int32_t*>(xmlTest.getSharedData()), reinterpret_cast<int32_t*>(sharedData));
			delete sharedData;
		}

		TEST_METHOD(setSharedData)
		{

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XMLParseMasterTest::sStartMemState;
}
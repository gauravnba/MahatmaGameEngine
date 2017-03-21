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

		TEST_METHOD(parseFromFileTest)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			XMLParseMaster xmlTest(sharedData);

			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			xmlTest.addHelper(xmlHelper);
			
			xmlTest.parseFromFile("..//..//..//..//..//test_files//Motorcycle.xml");

			Assert::AreEqual(xmlHelper->mFoundAttributes["Name"].size(), 3U);
			Assert::AreEqual(xmlHelper->mFoundAttributes["Brand"][0], string("Yamaha"));
			Assert::AreEqual(xmlHelper->mFoundAttributes["Brand"][1], string("Harley Davidson"));
			Assert::AreEqual(xmlHelper->mFoundAttributes["Brand"][2], string("BMW"));

			delete sharedData;
			delete xmlHelper;
		}

		TEST_METHOD(parseFromFileWithClone)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			XMLParseMaster xmlTest(sharedData);

			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			xmlTest.addHelper(xmlHelper);

			XMLParseMaster* xmlTest1 = xmlTest.clone();

			xmlTest1->parseFromFile("..//..//..//..//..//test_files//Motorcycle.xml");

			delete xmlTest1;

			delete sharedData;
			delete xmlHelper;
		}

		TEST_METHOD(cloneHelperTest)
		{
			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			XMLParseHelperMotorcycle* xmlHelper1 = xmlHelper->clone();

			delete xmlHelper1;
			delete xmlHelper;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XMLParseMasterTest::sStartMemState;
}
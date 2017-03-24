#include "pch.h"

#include "XMLParseMaster.h"
#include "XMLParseHelperMotorcycle.h"
#include "SharedDataMotorcycles.h"

#include "SharedDataCars.h"
#include "XMLParseHelperCars.h"


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
			XMLParseMaster xmlTest(*sharedData);

			Assert::AreEqual(reinterpret_cast<int32_t*>(xmlTest.getSharedData()), reinterpret_cast<int32_t*>(sharedData));
			delete sharedData;
		}

		TEST_METHOD(parseFromFileTest)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			XMLParseMaster xmlTest(*sharedData);

			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			xmlTest.addHelper(*xmlHelper);
			
			xmlTest.parseFromFile("..//..//..//..//..//test_files//Motorcycle.xml");

			Assert::AreEqual(sharedData->mFoundAttributes["Name"].size(), 3U);
			Assert::AreEqual(sharedData->mFoundAttributes["Brand"][0], string("Yamaha"));
			Assert::AreEqual(sharedData->mFoundAttributes["Brand"][1], string("Harley Davidson"));
			Assert::AreEqual(sharedData->mFoundAttributes["Brand"][2], string("BMW"));

			Assert::AreEqual(xmlTest.getFileName(), string("..//..//..//..//..//test_files//Motorcycle.xml"));

			auto invalidXMLException = [&xmlTest] {xmlTest.parseFromFile("..//..//..//..//..//test_files//Motorcycle_Invalid.xml"); };
			Assert::ExpectException<exception>(invalidXMLException);

			delete sharedData;
			delete xmlHelper;
		}

		TEST_METHOD(parseFromFileWithClone)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			XMLParseMaster xmlTest(*sharedData);

			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			xmlTest.addHelper(*xmlHelper);

			XMLParseMaster* xmlTest1 = xmlTest.clone();

			xmlTest.removeHelper(*xmlHelper);

			xmlTest1->parseFromFile("..//..//..//..//..//test_files//Motorcycle.xml");

			Assert::AreEqual(xmlTest1->getSharedData()->as<SharedDataMotorcycles>()->mFoundAttributes["Name"].size(), 3U);
			Assert::AreEqual(xmlTest1->getSharedData()->as<SharedDataMotorcycles>()->mFoundAttributes["Brand"][0], string("Yamaha"));
			Assert::AreEqual(xmlTest1->getSharedData()->as<SharedDataMotorcycles>()->mFoundAttributes["Brand"][1], string("Harley Davidson"));
			Assert::AreEqual(xmlTest1->getSharedData()->as<SharedDataMotorcycles>()->mFoundAttributes["Brand"][2], string("BMW"));

			Assert::AreNotEqual(sharedData->mFoundAttributes["Name"].size(), 3U);
			Assert::AreEqual(sharedData->mFoundAttributes["Name"].size(), 0U);

			delete xmlTest1;

			delete sharedData;
			delete xmlHelper;
		}

		TEST_METHOD(cloneHelperTest)
		{
			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			XMLParseHelperMotorcycle* xmlHelper1 = xmlHelper->clone();
			//Testing for memory leaks
			delete xmlHelper1;
			delete xmlHelper;
		}

		TEST_METHOD(setSharedDataTest)
		{
			SharedDataMotorcycles* sharedData = new SharedDataMotorcycles;
			SharedDataMotorcycles* sharedData1 = new SharedDataMotorcycles;

			XMLParseMaster xmlTest(*sharedData);

			xmlTest.setSharedData(*sharedData1);

			XMLParseHelperMotorcycle* xmlHelper = new XMLParseHelperMotorcycle;
			xmlTest.addHelper(*xmlHelper);

			xmlTest.parseFromFile("..//..//..//..//..//test_files//Motorcycle.xml");

			Assert::AreEqual(sharedData->mFoundAttributes["Name"].size(), 0U);
			Assert::AreEqual(reinterpret_cast<int32_t*>(xmlTest.getSharedData()), reinterpret_cast<int32_t*>(sharedData1));
			Assert::AreEqual(sharedData1->mFoundAttributes["Brand"][0], string("Yamaha"));
			Assert::AreEqual(sharedData1->mFoundAttributes["Brand"][1], string("Harley Davidson"));
			Assert::AreEqual(sharedData1->mFoundAttributes["Brand"][2], string("BMW"));

			Assert::AreEqual(xmlTest.getFileName(), string("..//..//..//..//..//test_files//Motorcycle.xml"));

			auto invalidXMLException = [&xmlTest] {xmlTest.parseFromFile("..//..//..//..//..//test_files//Motorcycle_Invalid.xml"); };
			Assert::ExpectException<exception>(invalidXMLException);

			delete sharedData;
			delete sharedData1;
			delete xmlHelper;
		}

		TEST_METHOD(testAttributeXMLParsing)
		{
			SharedDataCars* sharedData = new SharedDataCars;
			XMLParseMaster xmlTest(*sharedData);

			XMLParseHelperCars* xmlHelper = new XMLParseHelperCars;
			xmlTest.addHelper(*xmlHelper);

			xmlTest.parseFromFile("..//..//..//..//..//test_files//Cars.xml");

			Assert::AreEqual(sharedData->mFoundAttributes["Car"].size(), 3U);
			Assert::AreEqual(sharedData->mFoundAttributes["Car"].get<Scope*>(1)->append("brand").get<string>(0), string("Ford"));
			Assert::AreEqual(sharedData->mFoundAttributes["Car"].get<Scope*>(2)->append("brand").get<string>(0), string("Mercedes"));

			Assert::AreEqual(xmlTest.getFileName(), string("..//..//..//..//..//test_files//Cars.xml"));

			auto invalidXMLException = [&xmlTest] {xmlTest.parseFromFile("..//..//..//..//..//test_files//Cars_Invalid.xml"); };
			Assert::ExpectException<exception>(invalidXMLException);

			delete sharedData;
			delete xmlHelper;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XMLParseMasterTest::sStartMemState;
}
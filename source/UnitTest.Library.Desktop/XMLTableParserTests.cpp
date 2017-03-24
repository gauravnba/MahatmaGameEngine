#include "pch.h"

#include "CppUnitTest.h"

#include "XMLParseMaster.h"
#include "SharedDataTable.h"
#include "XMLParseHelperInteger.h"
#include "XMLParseHelperFloat.h"
#include "XMLParsehelperScope.h"
#include "XMLParseHelperVector.h"
#include "XMLParseHelperMatrix.h"
#include "XMLParseHelperString.h"
#include <cstring>
#include "glm.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(XMLTableParserTests)
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

		TEST_METHOD(integerParsingTest)
		{
			char* integerXML = "<Scope name = \"root\"><Integer name = \"first number\" value = \"10\"/></Scope>";

			SharedDataTable sharedData;
			XMLParseHelperInteger* integerHelper = new XMLParseHelperInteger;

			XMLParseMaster xmlMaster(sharedData);
			xmlMaster.addHelper(*integerHelper);
			xmlMaster.parse(integerXML, strlen(integerXML), true);
			Assert::AreEqual((*(sharedData.mCurrentTable))["first number"].get<int32_t>(), 10);

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();

			delete sharedData.mCurrentTable;

			xmlMasterClone->parse(integerXML, strlen(integerXML), true);
			SharedDataTable& clonedSharedData = *((xmlMasterClone->getSharedData())->as<SharedDataTable>());
			Assert::AreEqual((*(clonedSharedData.mCurrentTable))["first number"].get<int32_t>(), 10);

			delete clonedSharedData.mCurrentTable;

			delete xmlMasterClone;
			delete integerHelper;
		}

		TEST_METHOD(SharedDataTableRTTITest)
		{
			SharedDataTable sharedData;

			Assert::IsTrue(sharedData.is(SharedData::typeIdClass()));

			uint64_t sharedDataTypeId = sharedData.typeIdInstance();
			Assert::AreEqual(sharedData.typeIdClass(), sharedDataTypeId);

			SharedDataTable sharedDataNew;
			Assert::IsTrue(sharedData.equals(&sharedDataNew));

			Assert::AreEqual(sharedData.toString(), string("RTTI"));

			delete sharedData.mCurrentTable;
			delete sharedDataNew.mCurrentTable;
		}

		TEST_METHOD(floatingParsingTest)
		{
			char* floatXML = "<Scope name = \"root\"><Float name = \"first float\" value = \"10.5\"/></Scope>";

			SharedDataTable sharedData;
			XMLParseHelperFloat* floatHelper = new XMLParseHelperFloat;
			XMLParseHelperScope* scopeHelper = new XMLParseHelperScope;

			XMLParseMaster xmlMaster(sharedData);
			xmlMaster.addHelper(*floatHelper);
			xmlMaster.addHelper(*scopeHelper);
			xmlMaster.parse(floatXML, strlen(floatXML), true);
			Assert::AreEqual((*(sharedData.mCurrentTable))["first float"].get<float>(), 10.5f);

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();

			delete sharedData.mCurrentTable;

			xmlMasterClone->parse(floatXML, strlen(floatXML), true);
			SharedDataTable& clonedSharedData = *((xmlMasterClone->getSharedData())->as<SharedDataTable>());
			Assert::AreEqual((*(clonedSharedData.mCurrentTable))["first float"].get<float>(), 10.5f);

			delete clonedSharedData.mCurrentTable;

			delete xmlMasterClone;
			delete floatHelper;
			delete scopeHelper;
		}

		TEST_METHOD(scopeParsingTest)
		{
			char* scopeXML = "<Scope><Scope name = \"branch\"><Integer name = \"interior\" value = \"10\"/></Scope></Scope>";

			XMLParseHelperScope scopeHelper;
			XMLParseHelperInteger integerHelper;
			SharedDataTable sharedData;
			XMLParseMaster xmlParser(sharedData);
			xmlParser.addHelper(scopeHelper);
			xmlParser.addHelper(integerHelper);

			xmlParser.parse(scopeXML, strlen(scopeXML), true);

			Assert::AreEqual((*(sharedData.mCurrentTable))["branch"][0]["interior"].get<int32_t>(), 10);

			XMLParseMaster* xmlParserClone = xmlParser.clone();
			Scope& sharedCloneTable = *(xmlParserClone->getSharedData()->as<SharedDataTable>()->mCurrentTable);
			xmlParserClone->parse(scopeXML, strlen(scopeXML), true);

			Assert::AreEqual(sharedCloneTable["branch"][0]["interior"].get<int32_t>(), 10);

			delete sharedData.mCurrentTable;
			delete &sharedCloneTable;
			delete xmlParserClone;
		}

		TEST_METHOD(vectorParseTest)
		{
			glm::vec4 vectorVal(2.5f, 4.5f, 2.0f, 50.68f);
			char* vectorXML = "<Scope><Vector name = \"veccy\" value = \"vec4(2.5, 4.5, 2.0, 50.68)\"/></Scope>";
			XMLParseHelperVector vectorHelper;
			SharedDataTable sharedData;
			XMLParseMaster xmlMaster(sharedData);

			xmlMaster.addHelper(vectorHelper);
			xmlMaster.parse(vectorXML, strlen(vectorXML), true);

			Assert::AreEqual((*(sharedData.mCurrentTable))["veccy"].get<vec4>(), vectorVal);

			delete sharedData.mCurrentTable;

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();
			Scope& clonedSharedTable = *(xmlMasterClone->getSharedData()->as<SharedDataTable>()->mCurrentTable);

			xmlMasterClone->parse(vectorXML, strlen(vectorXML), true);

			Assert::AreEqual(clonedSharedTable["veccy"].get<vec4>(), vectorVal);

			delete &clonedSharedTable;
			delete xmlMasterClone;
		}

		TEST_METHOD(matrixParseTest)
		{
			char* matrixXML = "<Scope><Matrix name = \"matty\" value = \"mat4x4((1.5, 5.0, 4.5, 1.5), (5.5, 9.1, 7.1, 8), (8, 2.4, 6.5, 7.58), (8.1, 5.2, 6.9, 4.5))\"/></Scope>";
			glm::mat4x4 matrixVal(glm::vec4(1.5f, 5.0f, 4.5f, 1.5f), glm::vec4(5.5f, 9.1f, 7.1f, 8.0f), glm::vec4(8.0f, 2.4f, 6.5f, 7.58f), glm::vec4(8.1f, 5.2f, 6.9f, 4.5f));

			XMLParseHelperMatrix matrixHelper;
			SharedDataTable sharedData;
			XMLParseMaster xmlMaster(sharedData);

			xmlMaster.addHelper(matrixHelper);
			xmlMaster.parse(matrixXML, strlen(matrixXML), true);

			Assert::AreEqual((*(sharedData.mCurrentTable))["matty"].get<mat4x4>(), matrixVal);

			delete sharedData.mCurrentTable;

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();
			Scope& cloneSharedData = *(xmlMasterClone->getSharedData()->as<SharedDataTable>()->mCurrentTable);

			xmlMasterClone->parse(matrixXML, strlen(matrixXML), true);
			Assert::AreEqual(cloneSharedData["matty"].get<mat4x4>(), matrixVal);

			delete &cloneSharedData;
			delete xmlMasterClone;
		}

		TEST_METHOD(stringParserTest)
		{
			char* stringXML = "<Scope><String name = \"AmonAmarth\" value = \"Deceiver of Gods\"/></Scope>";
			XMLParseHelperString stringHelper;
			SharedDataTable sharedData;
			XMLParseMaster xmlMaster(sharedData);

			xmlMaster.addHelper(stringHelper);
			xmlMaster.parse(stringXML, strlen(stringXML), true);

			Assert::AreEqual((*(sharedData.mCurrentTable))["AmonAmarth"].get<string>(), string("Deceiver of Gods"));

			delete sharedData.mCurrentTable;

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();
			Scope& cloneSharedData = *(xmlMasterClone->getSharedData()->as<SharedDataTable>()->mCurrentTable);

			xmlMasterClone->parse(stringXML, strlen(stringXML), true);

			Assert::AreEqual(cloneSharedData["AmonAmarth"].get<string>(), string("Deceiver of Gods"));

			delete &cloneSharedData;
			delete xmlMasterClone;
		}

		TEST_METHOD(parseFromStringTest)
		{
			glm::vec4 vectorVal(2.5f, 4.5f, 2.0f, 50.68f);
			glm::mat4x4 matrixVal(glm::vec4(1.5f, 5.0f, 4.5f, 1.5f), glm::vec4(5.5f, 9.1f, 7.1f, 8.0f), glm::vec4(8.0f, 2.4f, 6.5f, 7.58f), glm::vec4(8.1f, 5.2f, 6.9f, 4.5f));
			XMLParseHelperInteger integerHelper;
			XMLParseHelperFloat floatHelper;
			XMLParseHelperVector vectorHelper;
			XMLParseHelperMatrix matrixHelper;
			XMLParseHelperScope tableHelper;
			XMLParseHelperString stringHelper;

			SharedDataTable sharedData;
			XMLParseMaster xmlMaster(sharedData);

			xmlMaster.addHelper(integerHelper);
			xmlMaster.addHelper(floatHelper);
			xmlMaster.addHelper(vectorHelper);
			xmlMaster.addHelper(matrixHelper);
			xmlMaster.addHelper(tableHelper);
			xmlMaster.addHelper(stringHelper);

			xmlMaster.parseFromFile("..//..//..//..//..//test_files//Table.xml");
			
			Assert::AreEqual((*(sharedData.mCurrentTable))["inty"].get<int32_t>(), 10);
			Assert::AreEqual((*(sharedData.mCurrentTable))["floaty"].get<float>(), 5.0f);
			Assert::AreEqual((*(sharedData.mCurrentTable))["veccy"].get<vec4>(), vectorVal);
			Assert::AreEqual((*(sharedData.mCurrentTable))["matty"].get<mat4x4>(), matrixVal);
			Assert::AreEqual((*(sharedData.mCurrentTable))["first branch"][0]["Amon Amarth"].get<string>(), string("Deceiver of Gods"));

			delete sharedData.mCurrentTable;

			XMLParseMaster* xmlMasterClone = xmlMaster.clone();
			xmlMasterClone->parseFromFile("..//..//..//..//..//test_files//Table.xml");

			Scope& cloneSharedData = *(xmlMasterClone->getSharedData()->as<SharedDataTable>()->mCurrentTable);
			Assert::AreEqual(cloneSharedData["inty"].get<int32_t>(), 10);
			Assert::AreEqual(cloneSharedData["floaty"].get<float>(), 5.0f);
			Assert::AreEqual(cloneSharedData["veccy"].get<vec4>(), vectorVal);
			Assert::AreEqual(cloneSharedData["matty"].get<mat4x4>(), matrixVal);
			Assert::AreEqual(cloneSharedData["first branch"][0]["Amon Amarth"].get<string>(), string("Deceiver of Gods"));

			delete &cloneSharedData;
			delete xmlMasterClone;
		}

	private:
		typedef XMLParseMaster::SharedData SharedData;
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XMLTableParserTests::sStartMemState;
}
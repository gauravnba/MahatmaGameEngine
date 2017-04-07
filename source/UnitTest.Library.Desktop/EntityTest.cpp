#include "pch.h"

#include "CppUnitTest.h"

#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "EntityFoo.h"
#include "GameTime.h"
#include "WorldState.h"
#include "XMLParseMaster.h"
#include "XMLParseHelperScope.h"
#include "XMLParseHelperDatum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(EntityTest)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeAttributedMap)
		{
			Entity tempEntity;
			Sector tempSector;
			World tempWorld;
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

		TEST_METHOD(entityMoveSemanticsTest)
		{
			Entity* testEntity = new Entity;

			testEntity->setName("Test");
			Assert::AreEqual(testEntity->name(), string("Test"));
			Assert::IsTrue(testEntity->isPrescribedAttribute("name"));

			Entity tempEntity(move(*testEntity));
			delete testEntity;
			Assert::AreEqual(tempEntity.name(), string("Test"));
			Assert::IsTrue(tempEntity.isPrescribedAttribute("name"));

			Entity* anotherTestEntity = new Entity;

			anotherTestEntity->setName("AnotherTest");
			Assert::AreEqual(anotherTestEntity->name(), string("AnotherTest"));
			Assert::IsTrue(anotherTestEntity->isPrescribedAttribute("name"));
			Entity anotherTempEntity;
			anotherTempEntity = move(*anotherTestEntity);
			delete anotherTestEntity;
			Assert::AreEqual(anotherTempEntity.name(), string("AnotherTest"));
			Assert::IsTrue(anotherTempEntity.isPrescribedAttribute("name"));
		}

		TEST_METHOD(entityGetSectorTest)
		{
			Entity* tempEntity = new Entity;
			Sector tempSector;
			tempEntity->setName("test");
			tempSector.adoptEntity(*tempEntity);
			Assert::AreEqual(tempSector.entities().size(), 1U);
			Assert::IsTrue(&tempSector == (tempEntity->getSector()));
		}

		TEST_METHOD(sectorCreateEntityTest)
		{
			EntityFactory entityFactory;
			Sector tempSector;
			Entity* tempEntity = &(tempSector.createEntity("Entity", "BrilliantName"));
			Assert::AreEqual(tempEntity->name(), static_cast<Entity&>(tempSector["entities"][0]).name());

			//Test with EntityFoo
			EntityFooFactory entityFooFactory;
			Entity* tempEntityFoo = &(tempSector.createEntity("EntityFoo", "NotVeryCreativeName"));
			UNREFERENCED_PARAMETER(tempEntityFoo);
			Assert::IsTrue(tempEntityFoo->is(EntityFoo::typeName()));
			Assert::AreEqual(tempEntityFoo->name(), static_cast<EntityFoo&>(tempSector["entities"][1]).name());
		}

		TEST_METHOD(worldNameConstructorTest)
		{
			World world("TestWorld");
			Assert::AreEqual(world.name(), string("TestWorld"));

			World worldNameLess;
			worldNameLess.setName("NotNameLess");
			Assert::AreEqual(worldNameLess.name(), string("NotNameLess"));
		}

		TEST_METHOD(worldMoveSemanticsTest)
		{
			World* world = new World("TestWorld");

			World tempWorld(move(*world));
			delete world;
			Assert::AreEqual(tempWorld.name(), string("TestWorld"));

			World* anotherWorld = new World("AnotherWorld");

			World tempWorld2;
			tempWorld2 = move(*anotherWorld);
			delete anotherWorld;
			Assert::AreEqual(tempWorld2.name(), string("AnotherWorld"));
		}

		TEST_METHOD(worldCreateSectorTest)
		{
			World tempWorld("Test");

			Sector& tempSector = tempWorld.createSector();
			Assert::IsTrue(tempWorld.sectors()[0].as<Sector>() == &tempSector);
			Assert::IsTrue(tempSector.getWorld() == &tempWorld);

			Sector& newSector =	tempWorld.createSector("New");
			Assert::IsTrue(newSector.name() == string("New"));
			newSector.setName("NotNewAnymore");
			Assert::AreEqual(newSector.name(), string("NotNewAnymore"));
		}

		TEST_METHOD(updateTest)
		{
			GameTime gameTime;
			GameClock gameClock;
			gameClock.reset();

			WorldState worldState;

			worldState.mGameTime = &gameTime;
			World world("CruelWorld");
			Sector* sector = &(world.createSector("BadSector"));
			EntityFactory entityFactory;
			EntityFooFactory entityFooFactory;
			Entity* entity = &(sector->createEntity("Entity", "OnlyGoodEntity"));
			Entity* entityFoo = &(sector->createEntity("EntityFoo", "JustAnotherBadEntity"));

			while (gameTime.totalGameTime() < std::chrono::milliseconds(1000))
			{
				gameClock.updateGameTime(gameTime);
				world.update(worldState);
			}

			Assert::AreNotEqual(static_cast<EntityFoo*>(entity)->getCounterValue(), 0U);
			Assert::IsTrue(worldState.mCurrentWorld == &world);
			Assert::IsTrue(worldState.mCurrentSector == sector);
			Assert::IsTrue(worldState.mCurrentEntity == entityFoo);
		}

		TEST_METHOD(entityParsingTest)
		{
			SharedDataTable sharedData;
			XMLParseMaster xmlParseMaster(sharedData);
			XMLParseHelperDatum datumHelper;
			XMLParseHelperScope scopeHelper;
			xmlParseMaster.addHelper(datumHelper);
			xmlParseMaster.addHelper(scopeHelper);
			EntityFooFactory entityFooFactory;

			xmlParseMaster.parseFromFile("test_scripts//EntityTest.xml");

			Assert::IsTrue((*(sharedData.mCurrentTable))["BigWorld"][0]["TestWorld"] == "ThisIsWorld");
			Assert::IsTrue((*(sharedData.mCurrentTable))["BigWorld"][0]["sectors"][0]["TestSector"] == "ThisIsSector");
			Assert::IsTrue((*(sharedData.mCurrentTable))["BigWorld"][0]["sectors"][0]["entities"][0].is(EntityFoo::typeName()));

			delete sharedData.mCurrentTable;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
}
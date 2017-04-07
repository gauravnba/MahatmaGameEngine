#include "pch.h"

#include "CppUnitTest.h"

#include "ActionFoo.h"
#include "ActionList.h"
#include "GameTime.h"
#include "ActionListIf.h"
#include "GameClock.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(ActionTest)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeAttributedMap)
		{
			Entity tempEntity;
			//Sector tempSector;
			//World tempWorld;
			ActionFoo tempFoo;
			ActionList tempList;
			ActionListIf actionIf;
			ActionCreateAction tempCreateAction;
			ActionDestroyAction tempDestroyAction;
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

		TEST_METHOD(actionListUpdateTest)
		{
			GameClock gameClock;
			GameTime gameTime;
			Entity entity;
			WorldState worldState;
			worldState.mGameTime = &gameTime;
			ActionListFactory actionFactory;

			Action* actionTest1 = &(entity.createAction("ActionList", "testAction"));
			Action* foo = new ActionFoo;
			foo->setName("Foo");
			actionTest1->adopt(foo, "actions");

			while (gameTime.totalGameTime() < std::chrono::milliseconds(1000))
			{
				gameClock.updateGameTime(gameTime);
				entity.update(worldState);
			}
			
			Assert::AreEqual(actionTest1->name(), string("testAction"));
			Assert::AreEqual(foo->name(), string("Foo"));
			Assert::IsTrue(static_cast<ActionFoo*>(actionTest1)->getCounterValue() > 0U);
			Assert::IsTrue(static_cast<ActionFoo*>(foo)->getCounterValue() > 0U);
		}

		TEST_METHOD(actionCreateDestroyActionTest)
		{
			ActionCreateActionFactory actionCreateFactory;
			ActionDestroyActionFactory actionDestroyFactory;
			ActionFooFactory actionFooFactory;

			Entity entity;
			WorldState worldState;
			Action* createAction = &(entity.createAction("ActionCreateAction", "createActionFoo"));
			static_cast<ActionCreateAction*>(createAction)->setPropertiesForAction("sampleFoo", "ActionFoo");
			entity.update(worldState);

			Assert::IsTrue(entity["actions"][1].is(ActionFoo::typeName()));
			delete createAction;

			Action* destroyAction = &(entity.createAction("ActionDestroyAction", "destroyActionFoo"));
			static_cast<ActionDestroyAction*>(destroyAction)->setAction("sampleFoo");
			entity.update(worldState);

			Assert::AreEqual(entity["actions"].size(), 1U);
			Assert::IsFalse(entity["actions"][0].is(ActionFoo::typeName()));
		}

		TEST_METHOD(actionListIfTest)
		{
			ActionFooFactory actionFooFactory;
			ActionListIfFactory actionIfFactory;
			Entity entity;
			WorldState worldState;
			ActionListIf& actionIf = static_cast<ActionListIf&>(entity.createAction("ActionListIf", "IfCondition"));
			entity["Condition"].pushBack(5);
			actionIf.setCondition("Condition");
			Action& actionThen = actionIf.createAction("ActionFoo", "then", true);
			Action& actionElse = actionIf.createAction("ActionFoo", "else", false);

			entity.update(worldState);
			Assert::AreEqual(static_cast<ActionFoo&>(actionThen).getCounterValue(), 1U);
			Assert::AreEqual(static_cast<ActionFoo&>(actionElse).getCounterValue(), 0U);

			entity["Condition"] = 0;
			entity.update(worldState);
			Assert::AreEqual(static_cast<ActionFoo&>(actionThen).getCounterValue(), 1U);
			Assert::AreEqual(static_cast<ActionFoo&>(actionElse).getCounterValue(), 1U);
		}


	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTest::sStartMemState;
}
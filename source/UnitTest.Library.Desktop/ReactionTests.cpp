#include "pch.h"

#include "CppUnitTest.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "AttributedMessage.h"
#include "ActionEvent.h"
#include "Factory.h"
#include "ActionSetString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(ReactionTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeEventList)
		{
			AttributedMessage message;
			ReactionAttributed reaction;
			ActionSetString action;
			ActionEvent actionEvent;
			World world;
		}

		//This method sets up the initial memory state to check for memory leaks.
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			Event<AttributedMessage>::unsubscribeAll();
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		//This test method checks the current memory state against the initial state to check for memory leaks.
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			Event<AttributedMessage>::unsubscribeAll();
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(attributedMessageCopyTest)
		{
			WorldState worldState;
			AttributedMessage message("copyTest", worldState);
			message.appendAuxiliaryAttribute("TestAtt") = "Test";
			AttributedMessage messageCopy = message;
			Assert::AreEqual(messageCopy["TestAtt"].get<string>(), string("Test"));
			Assert::AreEqual(message.getSubType(), messageCopy.getSubType());
			Assert::IsTrue(&message.getWorldState() == &messageCopy.getWorldState());

			messageCopy["TestAtt"] = "Copy Test";
			messageCopy.setSubType("assignmentTest");
			message = messageCopy;
			Assert::AreEqual(message.getSubType(), string("assignmentTest"));
			Assert::AreEqual(message["TestAtt"].get<string>(), string("Copy Test"));
		}

		TEST_METHOD(setSubTypeTest)
		{
			ReactionAttributed reaction;
			AttributedMessage message;
			message.setSubType("testMessageType");
			reaction.setSubType("testReactionType");
			Assert::AreEqual(message.getSubType(), string("testMessageType"));
			Assert::AreEqual(reaction.getSubType(), string("testReactionType"));
		}

		TEST_METHOD(reactionNotifyTest)
		{
			WorldState worldState;
			GameTime gameTime;
			worldState.mGameTime = &gameTime;
			AttributedMessage message("testType", worldState);
			message.appendAuxiliaryAttribute("testString") = "Test";
			Event<AttributedMessage> event(message);

			ReactionAttributed reaction;
			reaction.setSubType("testType");
			//reaction["testString"] = "Test";
			ActionSetString* action = new ActionSetString;
			action->setStringValues("testString", "Test Passed");
			reaction.adopt(action, "actions");
			reaction.notify(event);

			Assert::AreEqual(reaction["testString"].get<string>(), string("Test Passed"));			
		}

		TEST_METHOD(oldReactionNotifyTest)
		{
			WorldState worldState;
			GameTime gameTime;
			worldState.mGameTime = &gameTime;
			AttributedMessage message("testType", worldState);
			Event<AttributedMessage> event(message);

			ReactionAttributed reaction;
			reaction.setSubType("testType");
			reaction["testString"] = "Test";
			ActionSetString* action = new ActionSetString;
			action->setStringValues("testString", "Test Passed");
			reaction.adopt(action, "actions");
			reaction.notify(event);

			Assert::AreEqual(reaction["testString"].get<string>(), string("Test Passed"));
		}

		TEST_METHOD(actionEventUpdateTest)
		{
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionFactory;
			ActionSetStringFactory actionSetStringFactory;

			auto action = static_cast<ActionEvent*>(Factory<Action>::create("ActionEvent"));
			action->setAttributes("testType", 0);
			(*action)["testString"] = "Test";
			auto& reaction = *(static_cast<ReactionAttributed*>(Factory<Reaction>::create("ReactionAttributed")));
			reaction.setSubType("testType");
			auto& actionSetString = static_cast<ActionSetString&>(reaction.createAction("ActionSetString", "SetTestString"));
			actionSetString.setStringValues("testString", "Message received");

			WorldState worldState;
			EventQueue eventQueue;
			GameTime gameTime;
			worldState.mGameTime = &gameTime;
			worldState.mEventQueue = &eventQueue;
			action->update(worldState);
			eventQueue.update(gameTime);

			Assert::AreEqual(reaction["testString"].get<string>(), string("Message received"));

			delete action;
			delete &reaction;
		}

		TEST_METHOD(reactionParserTest)
		{
			//Initialize Parser
			SharedDataTable sharedData;
			XMLParseMaster xmlParseMaster(sharedData);
			XMLParseHelperDatum datumHelper;
			XMLParseHelperScope scopeHelper;
			XMLParseHelperAction actionHelper;
			xmlParseMaster.addHelper(datumHelper);
			xmlParseMaster.addHelper(scopeHelper);
			xmlParseMaster.addHelper(actionHelper);
			ActionSetStringFactory tempSetStringFactory;
			ReactionAttributedFactory reactionFactory;
			ActionEventFactory actionEventFactory;

			xmlParseMaster.parseFromFile("test_scripts//ReactionTest.xml");
			
			//Initialize update
			WorldState worldState;
			EventQueue eventQueue;
			GameTime gameTime;
			GameClock gameClock;
			gameTime.setCurrentTime(Clock::now());
			worldState.mGameTime = &gameTime;
			worldState.mEventQueue = &eventQueue;

			World& world = static_cast<World&>((*(sharedData.mCurrentTable))["BigWorld"][0]);
			Reaction& reaction = static_cast<Reaction&>(world["reactions"][0]);

			//Test if Event expires before delay.
			while (gameTime.totalGameTime() < 950ms)
			{
				gameClock.updateGameTime(gameTime);
				world.update(worldState);
				eventQueue.update(gameTime);
			}
			auto datumGetException = [&reaction] {reaction["StringToChange"].get<string>(); };
			Assert::ExpectException<exception>(datumGetException);

			//Test if event expires after delay.
			while (gameTime.totalGameTime() < 1050ms)
			{
				gameClock.updateGameTime(gameTime);
				world.update(worldState);
				eventQueue.update(gameTime);
			}

			Assert::AreEqual(reaction["StringToChange"].get<string>(), string("Test Passed"));

			delete sharedData.mCurrentTable;
		}

		TEST_METHOD(actionEventSetterAndGetterTest)
		{
			ActionEvent action;
			action.setSubType("setTest");
			Assert::AreEqual(action.getSubType(), string("setTest"));

			action.setDelay(1000);
			Assert::AreEqual(action.getDelay(), 1000U);

			action.setAttributes("setAttributes", 10U);
			Assert::AreNotEqual(action.getDelay(), 1000U);
			Assert::AreEqual(action.getDelay(), 10U);
			Assert::AreNotEqual(action.getSubType(), string("setTest"));
			Assert::AreEqual(action.getSubType(), string("setAttributes"));
		}

		TEST_METHOD(attributedMessageSetWorldStateTest)
		{
			WorldState worldState;
			AttributedMessage message;
			message.setWorldState(worldState);
			Assert::IsTrue(&worldState == &(message.getWorldState()));
			message.setSubType("subType");
			Assert::AreEqual(string("subType"), message.getSubType());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTests::sStartMemState;
}
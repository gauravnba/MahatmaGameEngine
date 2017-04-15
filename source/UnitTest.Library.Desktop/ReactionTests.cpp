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

		TEST_METHOD(attributedEventCopyTest)
		{
			WorldState worldState;
			AttributedMessage event("copyTest", worldState);
			AttributedMessage eventCopy = event;
			Assert::AreEqual(event.getSubType(), eventCopy.getSubType());
			Assert::IsTrue(&event.getWorldState() == &eventCopy.getWorldState());

			eventCopy.setSubType("assignmentTest");
			event = eventCopy;
			Assert::AreEqual(event.getSubType(), string("assignmentTest"));
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
			Event<AttributedMessage> event(message);

			ReactionAttributed reaction;
			reaction.setSubType("testType");
			reaction["testString"] = "Test";
			Assert::AreEqual(reaction["testString"].get<string>(), string("Test"));
			ActionSetString* action = new ActionSetString;
			action->setStringValues("testString", "Test Passed");
			reaction.adopt(action, "actions");
			Scope* scope = nullptr;
			Assert::IsTrue(reaction["testString"] == *(reaction.search("testString", &scope)));
			Assert::IsNotNull(action->search("testString", &scope));
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
			auto& reaction = *(static_cast<ReactionAttributed*>(Factory<Reaction>::create("ReactionAttributed")));
			reaction.setSubType("testType");
			reaction["testString"] = "Test";
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

			WorldState worldState;
			EventQueue eventQueue;
			GameTime gameTime;
			worldState.mGameTime = &gameTime;
			worldState.mEventQueue = &eventQueue;
			World& world = static_cast<World&>((*(sharedData.mCurrentTable))["BigWorld"][0]);
			world.update(worldState);
			eventQueue.update(gameTime);

			Assert::AreEqual(world["StringToChange"].get<string>(), string("Test Passed"));

			delete sharedData.mCurrentTable;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTests::sStartMemState;
}
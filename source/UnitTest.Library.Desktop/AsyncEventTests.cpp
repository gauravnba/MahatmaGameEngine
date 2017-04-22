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
	TEST_CLASS(AsyncEventTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeEventList)
		{
			Foo tempFoo;
			Event<Foo> tempEvent(tempFoo);
		}

		//This method sets up the initial memory state to check for memory leaks.
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			Event<Foo>::unsubscribeAll();
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		//This test method checks the current memory state against the initial state to check for memory leaks.
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			Event<Foo>::unsubscribeAll();
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(asyncPublisherDeliverTest)
		{
			//Subscribe test
			for (uint32_t count = 0; count < 3; ++count)
			{
				SubscriberFoo subscriber;
				Event<Foo>::subscribe(subscriber);
			}

			SubscriberFoo subscriber;
			Event<Foo>::subscribe(subscriber);

			Foo foo(1);
			Event<Foo> event(foo);

			//Deliver test
			event.deliver();
			
			Assert::AreEqual(subscriber.getValue(), 1U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncEventTests::sStartMemState;
}
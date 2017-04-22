#include "pch.h"

#include "CppUnitTest.h"
#include "Event.h"
#include "EventQueue.h"
#include "Foo.h"
#include "SubscriberFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(EventTest)
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

		TEST_METHOD(eventConstructorTest)
		{
			Foo foo;
			Event<Foo> event(foo);

			Assert::IsTrue(event.message() == foo);

			//RTTI Tests
			Assert::AreEqual(Event<Foo>::typeName(), string("Event"));
			Assert::AreEqual(Event<Foo>::typeIdClass(), event.typeIdInstance());
			Assert::IsTrue(event.is(Event<Foo>::typeIdClass()));
			Assert::IsFalse(event.is(Event<int32_t>::typeIdClass()));
			Assert::IsNotNull(event.as<EventPublisher>());
			Assert::IsNotNull(event.queryInterface(EventPublisher::typeIdClass()));
		}

		TEST_METHOD(copySemanticsTest)
		{
			//Copy constructor
			Foo foo;
			Event<Foo> event(foo);
			event.setTime(Clock::now(), MilliSeconds(100));
			Event<Foo> eventCopy = event;
			Assert::IsTrue(event.message() == eventCopy.message());
			Assert::IsTrue(event.timeEnqueued() == eventCopy.timeEnqueued());

			//Copy assignment
			Foo fooNew;
			foo.setVar(20);
			Event<Foo> eventNew(fooNew);
			eventNew.setTime(Clock::now(), MilliSeconds(600));
			eventCopy = eventNew;
			Assert::IsTrue(eventNew.message() == eventCopy.message());
			Assert::IsTrue(eventNew.timeEnqueued() == eventCopy.timeEnqueued());
		}

		TEST_METHOD(moveSemanticsTest)
		{
			//Move constructor
			Foo foo;
			Event<Foo>* event = new Event<Foo>(foo);
			TimePoint timePoint = Clock::now();
			event->setTime(timePoint, MilliSeconds(100));
			Event<Foo> eventMove = move(*event);
			delete event;
			Assert::IsTrue(foo == eventMove.message());
			Assert::IsTrue(timePoint == eventMove.timeEnqueued());

			//Move assignment
			Foo fooNew(20);
			Event<Foo>* eventNew = new Event<Foo>(fooNew);
			timePoint = Clock::now();
			eventNew->setTime(timePoint, MilliSeconds(600));
			eventMove = move(*eventNew);
			delete eventNew;
			Assert::IsTrue(fooNew == eventMove.message());
			Assert::IsTrue(timePoint == eventMove.timeEnqueued());
		}

		TEST_METHOD(deliverTest)
		{
			//Subscribe test
			SubscriberFoo subscriber1;
			SubscriberFoo subscriber2;
			SubscriberFoo subscriber3;
			Event<Foo>::subscribe(subscriber1);
			Event<Foo>::subscribe(subscriber2);
			Event<Foo>::subscribe(subscriber3);
			Foo foo(1);
			Event<Foo> event(foo);

			////Deliver test
			//event.deliver();
			//Assert::AreEqual(subscriber1.getValue(), 1U);

			////Unsubscribe test
			////Event<Foo>::unsubscribe(subscriber1);
			////event.deliver();
			////Assert::AreEqual(subscriber2.getValue(), 2U);
			////Assert::AreNotEqual(subscriber1.getValue(), 2U);

			//////UnsubscribeAll test
			////Event<Foo>::unsubscribeAll();
			////event.deliver();
			////Assert::AreNotEqual(subscriber3.getValue(), 3U);
			////Assert::AreEqual(subscriber3.getValue(), 2U);
			////Assert::AreNotEqual(subscriber2.getValue(), 3U);
		}

		TEST_METHOD(enqueueTest)
		{
			Foo foo(10);
			GameTime gameTime;
			gameTime.setCurrentTime(Clock::now());
			shared_ptr<Event<Foo>> eventFoo = make_shared<Event<Foo>>(foo);

			Assert::IsTrue(eventFoo->isExpired(gameTime.currentTime()));

			EventQueue eventQueue;
			eventQueue.enqueue(eventFoo, gameTime, 1000ms);
			Assert::IsTrue(eventFoo->timeEnqueued() == gameTime.currentTime());
			Assert::IsFalse(eventFoo->isExpired(gameTime.currentTime()));
			Assert::AreEqual(eventQueue.size(), 1U);

			//using default arguments
			Foo foo1(20);
			shared_ptr<Event<Foo>> eventSecond = make_shared<Event<Foo>>(foo1);
			gameTime.setCurrentTime(Clock::now());
			eventQueue.enqueue(eventSecond, gameTime);
			Assert::IsTrue(eventSecond->isExpired(Clock::now()));
			Assert::AreEqual(eventQueue.size(), 2U);
		}

		TEST_METHOD(eQueueSendTest)
		{
			Foo foo(1);
			SubscriberFoo subscriber;
			Event<Foo>::subscribe(subscriber);
			Event<Foo> event(foo);
			EventQueue eQueue;
			eQueue.send(event);

			Assert::AreEqual(subscriber.getValue(), 1U);
		}

		TEST_METHOD(eQueueUpdateTest)
		{
			EventQueue eQueue;
			GameTime gameTime;
			GameClock gameClock;

			Foo foo1(1);
			SubscriberFoo subscriber1;
			Event<Foo>::subscribe(subscriber1);
			shared_ptr<Event<Foo>> event1 = make_shared<Event<Foo>>(foo1);
			Foo foo2(2);
			shared_ptr<Event<Foo>> event2 = make_shared<Event<Foo>>(foo2);
			Foo foo3(3);
			shared_ptr<Event<Foo>> event3 = make_shared<Event<Foo>>(foo3);
			gameTime.setCurrentTime(Clock::now());
			eQueue.enqueue(event1, gameTime);
			eQueue.enqueue(event2, gameTime, 2000ms);
			eQueue.enqueue(event3, gameTime);

			while (gameTime.totalGameTime() < 1000ms)
			{
				gameClock.updateGameTime(gameTime);
				eQueue.update(gameTime);
			}

			Assert::AreEqual(subscriber1.getValue(), 4U);
			gameTime.setCurrentTime(Clock::now());

			while (gameTime.totalGameTime() < 3000ms)
			{
				gameClock.updateGameTime(gameTime);
				eQueue.update(gameTime);
			}

			Assert::AreEqual(subscriber1.getValue(), 6U);
		}

		TEST_METHOD(eQueueClearTest)
		{
			EventQueue eQueue;
			GameTime gameTime;
			GameClock gameClock;

			Foo foo1(1);
			SubscriberFoo subscriber1;
			Event<Foo>::subscribe(subscriber1);
			shared_ptr<Event<Foo>> event1 = make_shared<Event<Foo>>(foo1);
			Foo foo2(2);
			shared_ptr<Event<Foo>> event2 = make_shared<Event<Foo>>(foo2);
			Foo foo3(3);
			shared_ptr<Event<Foo>> event3 = make_shared<Event<Foo>>(foo3);
			gameTime.setCurrentTime(Clock::now());
			eQueue.enqueue(event1, gameTime);
			eQueue.enqueue(event2, gameTime, 2000ms);
			eQueue.enqueue(event3, gameTime);

			Assert::IsFalse(eQueue.isEmpty());
			Assert::AreEqual(eQueue.size(), 3U);

			eQueue.clear(true);
			Assert::IsTrue(eQueue.isEmpty());
			Assert::AreEqual(subscriber1.getValue(), 4U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
}
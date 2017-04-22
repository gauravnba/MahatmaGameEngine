#include "pch.h"

#include "CppUnitTest.h"
#include "Event.h"
#include "EventQueue.h"
#include "Foo.h"
#include "SubscriberFoo.h"
#include "SubscriberUnsubsribeAll.h"
#include "SubscriberAdd.h"
#include "SubscriberAddEvent.h"

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
			//Subscribe test
			for (uint32_t count = 0; count < mNumSubscribers; ++count)
			{
				SubscriberFoo subscriber;
				Event<Foo>::subscribe(subscriber);
			}
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
			Vector<shared_ptr<SubscriberFoo>> subscribers;
			for (uint32_t i = 0; i < mNumSubscribers; ++i)
			{
				shared_ptr<SubscriberFoo> subscriber = make_shared<SubscriberFoo>();
				subscribers.pushBack(subscriber);
			}
			//Subscribe test
			for (uint32_t count = 0; count < mNumSubscribers; ++count)
			{
				Event<Foo>::subscribe(*subscribers[count]);
			}

			Foo foo(1);
			Event<Foo> event(foo);
			for (uint32_t i = 0; i < mNumSubscribers; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 0U);
			}
			//Deliver test
			event.deliver();
			for (uint32_t i = 0; i < mNumSubscribers; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 1U);
			}
		}

		TEST_METHOD(clearSubscriberListTest)
		{
			Vector<shared_ptr<SubscriberFoo>> subscribers;
			for (uint32_t i = 0; i < mNumSubscribers - 1; ++i)
			{
				shared_ptr<SubscriberFoo> subscriber = make_shared<SubscriberFoo>();
				subscribers.pushBack(subscriber);
			}
			//Subscribe test
			for (uint32_t count = 0; count < mNumSubscribers / 2; ++count)
			{
				Event<Foo>::subscribe(*subscribers[count]);
			}

			SubscriberUnsubscribeAll subscriber;
			Event<Foo>::subscribe(subscriber);

			for (uint32_t count = (mNumSubscribers/2); count < mNumSubscribers - 1; ++count)
			{
				Event<Foo>::subscribe(*subscribers[count]);
			}

			Event<Foo> event(Foo(1));
			for (uint32_t i = 0; i < mNumSubscribers - 1; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 0U);
			}

			//Test if all events deliver despite the unsubscribe call in between.
			event.deliver();
			for (uint32_t i = 0; i < mNumSubscribers - 1; ++i)
			{
				Assert::AreEqual(1U, subscribers[i]->getValue());
			}

			//Test if events still update on deliver, if unsubscribed.
			event.deliver();
			for (uint32_t i = 0; i < mNumSubscribers - 1; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 1U);
			}
		}

		TEST_METHOD(addSubscriptionTest)
		{
			//Create list of subscribers
			Vector<shared_ptr<SubscriberFoo>> subscribers;
			for (uint32_t i = 0; i < mNumSubscribers - 2; ++i)
			{
				shared_ptr<SubscriberFoo> subscriber = make_shared<SubscriberFoo>();
				subscribers.pushBack(subscriber);
			}
			for (uint32_t count = 0; count < mNumSubscribers / 2; ++count)
			{
				Event<Foo>::subscribe(*subscribers[count]);
			}
			//Subscribe SubscriberAdd in the middle of Event<Foo>
			SubscriberAdd subscriber;
			Event<Foo>::subscribe(subscriber);

			for (uint32_t count = (mNumSubscribers / 2); count < mNumSubscribers - 2; ++count)
			{
				Event<Foo>::subscribe(*subscribers[count]);
			}

			Event<Foo> event(Foo(1));
			for (uint32_t i = 0; i < mNumSubscribers - 2; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 0U);
			}

			//Test if all events deliver despite the unsubscribe call in between.
			event.deliver();
			for (uint32_t i = 0; i < mNumSubscribers - 2; ++i)
			{
				Assert::AreEqual(subscribers[i]->getValue(), 1U);
			}
			Assert::AreEqual(subscriber.getNewSubscriber()->getValue(), 0U);
			Event<Foo>::unsubscribe(subscriber);
			event.deliver();
			Assert::AreEqual(subscriber.getNewSubscriber()->getValue(), 1U);
		}

		TEST_METHOD(testSubscriberAddEvent)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			SubscriberAddEvent subscriber(eventQueue, gameTime);
			Event<Foo> temp(Foo(1));
			Assert::AreEqual(eventQueue.size(), 0U);
			subscriber.notify(temp);
			Assert::AreEqual(eventQueue.size(), 1U);
		}

		TEST_METHOD(subscriberEnqueueTest)
		{
			EventQueue eventQueue;
			GameTime gameTime;

			Vector<shared_ptr<SubscriberFoo>> subscribers;
			for (uint32_t i = 0; i < mNumSubscribers - 2; ++i)
			{
				shared_ptr<SubscriberFoo> subscriber = make_unique<SubscriberFoo>();
				subscribers.pushBack(subscriber);
				Event<Foo>::subscribe(*subscriber);
			}

			SubscriberAddEvent subscriber(eventQueue, gameTime);
			Event<Foo>::subscribe(subscriber);

			Vector<shared_ptr<Event<Foo>>> events;
			for (uint32_t i = 0; i < 100; ++i)
			{
				Foo foo(1);
				shared_ptr<Event<Foo>> event = make_shared<Event<Foo>>(foo);
				events.pushBack(event);
				eventQueue.enqueue(event, gameTime);
			}
			Assert::AreEqual(100U, eventQueue.size());

			gameTime.setCurrentTime(Clock::now());
			eventQueue.update(gameTime);
			Assert::AreEqual(100U, eventQueue.size());

			Event<Foo>::unsubscribe(subscriber);
			gameTime.setCurrentTime(Clock::now());
			eventQueue.update(gameTime);
			Assert::AreEqual(0U, eventQueue.size());
		}

		TEST_METHOD(subscriberClearTest)
		{

		}

	private:
		static _CrtMemState sStartMemState;
		static const uint32_t mNumSubscribers = 10000;
	};

	_CrtMemState AsyncEventTests::sStartMemState;
}
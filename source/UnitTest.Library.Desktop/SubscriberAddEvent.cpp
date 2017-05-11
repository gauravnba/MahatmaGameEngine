#include "pch.h"
#include "SubscriberAddEvent.h"
#include "Event.h"
#include "GameTime.h"
#include <future>

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;

SubscriberAddEvent::SubscriberAddEvent(EventQueue& eventQueue, GameTime& gameTime) :
	mEventQueue(&eventQueue), mGameTime(gameTime)
{
}

void SubscriberAddEvent::notify(const EventPublisher& subscribedTo)
{
	std::lock_guard<std::mutex> lock(mMutex);

	UNREFERENCED_PARAMETER(subscribedTo);
	mEvent = std::make_shared<Event<Foo>>(Foo(1));
	mEventQueue->enqueue(mEvent, mGameTime);
}

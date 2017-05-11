#include "pch.h"
#include "SubscriberAdd.h"
#include "SubscriberFoo.h"
#include <future>

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;

void SubscriberAdd::notify(const EventPublisher& subscribedTo)
{
	UNREFERENCED_PARAMETER(subscribedTo);
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mFoo = std::make_unique<SubscriberFoo>();
	}
	Event<Foo>::subscribe(*mFoo);
}

SubscriberFoo* SubscriberAdd::getNewSubscriber()
{
	return mFoo.get();
}
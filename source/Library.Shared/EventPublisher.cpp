#include "pch.h"
#include "EventPublisher.h"
#include <vector>
#include <future>

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(EventPublisher)

EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscriberList, mutex& mut) :
	mSubscribers(&subscriberList), mMutex(&mut)
{
}

EventPublisher::EventPublisher(const EventPublisher& obj) :
	mSubscribers(obj.mSubscribers), mTimeEnqueued(obj.mTimeEnqueued), mDelay(obj.mDelay), mMutex(obj.mMutex)
{
}

EventPublisher::EventPublisher(EventPublisher&& obj) :
	mTimeEnqueued(move(obj.mTimeEnqueued)), mDelay(move(obj.mDelay)), mSubscribers(obj.mSubscribers)
{
	obj.mMutex = nullptr;
	obj.mSubscribers = nullptr;
}

EventPublisher& EventPublisher::operator=(const EventPublisher& obj)
{
	if (this != &obj)
	{
		mSubscribers = obj.mSubscribers;
		mTimeEnqueued = obj.mTimeEnqueued;
		mDelay = obj.mDelay;
		mMutex = obj.mMutex;
	}
	return *this;
}

EventPublisher& EventPublisher::operator=(EventPublisher&& obj)
{
	if (this != &obj)
	{
		mSubscribers = obj.mSubscribers;
		mTimeEnqueued = move(obj.mTimeEnqueued);
		mDelay = move(obj.mDelay);
		mMutex = obj.mMutex;

		obj.mSubscribers = nullptr;
		obj.mMutex = nullptr;
	}
	return *this;
}

void EventPublisher::setTime(const TimePoint& time, const MilliSeconds& delay)
{
	mTimeEnqueued = time;
	mDelay = delay;
}

TimePoint& EventPublisher::timeEnqueued()
{
	return mTimeEnqueued;
}

bool EventPublisher::isExpired(const TimePoint& currentTime)
{
	if (currentTime >= (mTimeEnqueued + mDelay))
	{
		return true;
	}
	return false;
}

void EventPublisher::deliver()
{
	//Copy of list of subscribers that will be used asynchronously to call notify on each.
	Vector<EventSubscriber*> subscribersCopy;
	{
		lock_guard<mutex> lock(*mMutex);
		subscribersCopy = *mSubscribers;
	}

	vector<future<void>> futures;

	for (auto subscriber : subscribersCopy)
	{
		futures.emplace_back(std::async(&EventSubscriber::notify, subscriber, cref(*this)));
	}

	uint32_t size = futures.size();
	while (--size <= 0)
	{
		futures[size].get();
	}
}
#include "pch.h"
#include "EventQueue.h"
#include <vector>
#include <future>

using namespace MahatmaGameEngine;
using namespace std;

void EventQueue::enqueue(shared_ptr<EventPublisher> event, const GameTime& time, const MilliSeconds& delay)
{
	event->setTime(time.currentTime(), delay);
	{
		lock_guard<mutex> lock(mMutex);
		mEventQueue.pushBack(event);
	}
}

void EventQueue::send(EventPublisher& event)
{
	event.deliver();
}

void EventQueue::update(const GameTime& time)
{
	sendExpiredEvents(time.currentTime());
}

void EventQueue::clear(bool sendExpired)
{
	if (sendExpired)
	{
		sendExpiredEvents(Clock::now());
	}

	{
		lock_guard<mutex> lock(mMutex);
		mEventQueue.clear();
	}
}

void EventQueue::sendExpiredEvents(const TimePoint & timePoint)
{
	uint32_t size = mEventQueue.size();
	uint32_t expiredIndex = size;
	Vector<shared_ptr<EventPublisher>> queueCopy;

	//For partitioning of the expired and existent events.
	{
		lock_guard<mutex> lock(mMutex);
		for (uint32_t i = 0; i < expiredIndex; ++i)
		{
			if (mEventQueue[i]->isExpired(timePoint))
			{
				//Get index of the first event from the send that is not expired.
				while ((expiredIndex > i) && (mEventQueue[--expiredIndex]->isExpired(timePoint)));

				mEventQueue[i].swap(mEventQueue[expiredIndex]);
			}
		}

		for (uint32_t i = 0; i < (size - expiredIndex); ++i)
		{
			queueCopy.pushBack(mEventQueue.popBack());
		}
	}

	vector<future<void>> futures;

	for (auto& event : queueCopy)
	{
		futures.emplace_back(async(&EventPublisher::deliver, event));
	}
	
	for (auto& f : futures)
	{
		f.get();
	}
}

bool EventQueue::isEmpty()
{
	lock_guard<mutex> lock(mMutex);
	return mEventQueue.isEmpty();
}

uint32_t EventQueue::size()
{
	lock_guard<mutex> lock(mMutex);
	return mEventQueue.size();
}
#include "pch.h"
#include "EventQueue.h"

using namespace MahatmaGameEngine;
using namespace std;

void EventQueue::enqueue(shared_ptr<EventPublisher> event, const GameTime& time, const MilliSeconds& delay)
{
	event->setTime(time.currentTime(), delay);
	mEventQueue.pushBack(event);
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
	mEventQueue.clear();
}

void EventQueue::sendExpiredEvents(const TimePoint & timePoint)
{
	int32_t size = mEventQueue.size();
	int32_t expiredIndex = size;
	Vector<shared_ptr<EventPublisher>> queueCopy;

	//For partitioning of the expired and existent events.
	{
		lock_guard<mutex> lock(mMutex);
		for (int32_t i = 0; i < expiredIndex; ++i)
		{
			if (mEventQueue[i]->isExpired(timePoint))
			{
				//Get index of the first event from the send that is not expired.
				while ((expiredIndex > i) && (mEventQueue[--expiredIndex]->isExpired(timePoint)));

				mEventQueue[i].swap(mEventQueue[expiredIndex]);
				queueCopy.pushBack(mEventQueue.popBack());
			}
		}
	}

	//deliver event and then remove it from the queue.
	size = queueCopy.size();
	while (!queueCopy.isEmpty())
	{
		queueCopy[--size]->deliver();
	}
}

bool EventQueue::isEmpty()
{
	return mEventQueue.isEmpty();
}

uint32_t EventQueue::size()
{
	return mEventQueue.size();
}
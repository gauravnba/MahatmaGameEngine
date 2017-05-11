#include "pch.h"
#include "SubscriberClearQueue.h"
#include "EventQueue.h"

using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	SubscriberClearQueue::SubscriberClearQueue(MahatmaGameEngine::EventQueue& eventQueue) :
		mEventQueue(&eventQueue)
	{
	}

	void SubscriberClearQueue::notify(const MahatmaGameEngine::EventPublisher& subscribedTo)
	{
		UNREFERENCED_PARAMETER(subscribedTo);
		std::lock_guard<std::mutex> lock(mMutex);
		mEventQueue->clear();
	}
}
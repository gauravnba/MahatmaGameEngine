#pragma once

#include "EventSubscriber.h"
#include <mutex>

namespace UnitTestLibraryDesktop
{
	class MahatmaGameEngine::EventQueue;

	class SubscriberClearQueue : public MahatmaGameEngine::EventSubscriber
	{
	public:
		SubscriberClearQueue(MahatmaGameEngine::EventQueue& eventQueue);

		virtual void notify(const MahatmaGameEngine::EventPublisher& subscribedTo) override;
	private:
		MahatmaGameEngine::EventQueue* mEventQueue;
		std::mutex mMutex;
	};
}
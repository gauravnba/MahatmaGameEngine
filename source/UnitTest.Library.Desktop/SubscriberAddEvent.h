#pragma once

#include "EventSubscriber.h"
#include "Event.inl"
#include "Foo.h"
#include <memory>
#include <mutex>

namespace UnitTestLibraryDesktop
{
	class MahatmaGameEngine::GameTime;
	class SubscriberAddEvent : public MahatmaGameEngine::EventSubscriber
	{
	public:
		SubscriberAddEvent(MahatmaGameEngine::EventQueue& eventQueue, MahatmaGameEngine::GameTime& gameTime);

		virtual void notify(const MahatmaGameEngine::EventPublisher& subscribedTo) override;

	private:
		MahatmaGameEngine::EventQueue* mEventQueue;
		std::shared_ptr<MahatmaGameEngine::Event<Foo>> mEvent;
		MahatmaGameEngine::GameTime& mGameTime;
		std::mutex mMutex;
	};
}
#pragma once

#include "EventSubscriber.h"
#include <memory>

namespace UnitTestLibraryDesktop
{
	class SubscriberAdd : public MahatmaGameEngine::EventSubscriber
	{
	public:
		virtual void notify(const MahatmaGameEngine::EventPublisher& subscribedTo) override;

		SubscriberFoo* getNewSubscriber();

	private:
		std::unique_ptr<SubscriberFoo> mFoo;
		std::mutex mMutex;
	};
}
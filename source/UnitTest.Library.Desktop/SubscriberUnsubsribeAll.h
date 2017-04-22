#pragma once

#include "EventSubscriber.h"

namespace UnitTestLibraryDesktop
{
	class SubscriberUnsubscribeAll : public MahatmaGameEngine::EventSubscriber
	{
	public:
		virtual void notify(const MahatmaGameEngine::EventPublisher& subscribedTo) override;
	};
}
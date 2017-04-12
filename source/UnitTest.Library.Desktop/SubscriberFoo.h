#pragma once

#include "EventSubscriber.h"

namespace UnitTestLibraryDesktop
{
	class SubscriberFoo final : public MahatmaGameEngine::EventSubscriber
	{
	public:
		SubscriberFoo();

		virtual void notify(const MahatmaGameEngine::EventPublisher& publisher) override;

		std::uint32_t getValue();
	private:
		std::uint32_t mValue;
	};
}
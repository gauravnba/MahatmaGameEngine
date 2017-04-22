#pragma once

#include "EventSubscriber.h"
#include <functional>
#include "HashMap.h"
#include <mutex>

namespace UnitTestLibraryDesktop
{
	class SubscriberFoo final : public MahatmaGameEngine::EventSubscriber
	{
		typedef std::pair<std::string, std::function<void(const MahatmaGameEngine::EventPublisher&)>> functionPair;
	public:
		SubscriberFoo();

		virtual void notify(const MahatmaGameEngine::EventPublisher& publisher) override;

		std::uint32_t getValue();
	private:
		std::uint32_t mValue;
		std::mutex mMutex;
	};
}
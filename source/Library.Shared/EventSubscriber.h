#pragma once
#include "RTTI.h"

namespace MahatmaGameEngine
{
	class EventPublisher;

	class EventSubscriber
	{
	public:
		/**
		* Default destructor of EventSubscriber.
		*/
		virtual ~EventSubscriber() = default;

		/**
		* Pure virtual method Handlers will use the RTTI interface to verify the event type and then notify to the Publisher to add to Add to subsscriber queue.
		* @param subscribedTo address of EventPublisher to notify about subscription.
		*/
		virtual void notify(const EventPublisher& subscribedTo) = 0;
	};
}
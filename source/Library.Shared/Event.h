#pragma once

#include "EventPublisher.h"
#include "RTTI.h"

namespace MahatmaGameEngine
{
	template <typename T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)
	public:
		/**
		* Event constructed using message and whether to delete the message after.
		* @param eventMessage the message payload of this event.
		* @param deleteAfter is set to true if the event has to be deleted after publishing. False by default.
		*/
		Event(const T& eventMessage);

		/**
		* Deep copy constructor of Event.
		* @param obj the object to copy from.
		*/
		Event(const Event& obj);

		/**
		* Move constructor for Event.
		* @param obj the Event rvalue reference to move from.
		*/
		Event(Event&& obj);

		/**
		* Default destructor of Event.
		*/
		virtual ~Event() = default;

		/**
		* Copy assignment operator for Events.
		* @param obj the Event to copy from.
		* @return Event reference to this object that was copied to.
		*/
		Event& operator=(const Event& obj);

		/**
		* Move assignment operator for Events.
		* @param obj the Event rvalue reference to move from
		* @return Event reference to this object that was moved to.
		*/
		Event& operator=(Event&& obj);

		/**
		* Subscribe a subscriber to this event
		* @param subscriber EventSubscriber reference to subscribe to this event.
		*/
		static void subscribe(const EventSubscriber& subscriber);

		/**
		* Unsubscribe a subscriber from this event
		* @param subscriber EventSubscriber reference to unsubscribe from this event.
		*/
		static void unsubscribe(const EventSubscriber& subscriber);

		/**
		* Unsubscribes all subscribers from this event.
		*/
		static void unsubscribeAll();

		/**
		* Accessor for the message payload of this event.
		* @return Address of T of the message of this event.
		*/
		const T& message() const;

	private:
		static Vector<EventSubscriber*> mSubscribers;	/**< The list of EventSubscribers subscribed to this event. */
		T mPayload;										/**< The payload that the event is tasked to deliver. */
		static std::mutex mMutex;						/**< Static mutex to use to lock mSubscribers. */
	};

	template <typename T>
	RTTI_DEFINITIONS(Event<T>)
}

#include "Event.inl"
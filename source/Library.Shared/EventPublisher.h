#pragma once

#include "RTTI.h"
#include <chrono>
#include "Vector.h"
#include "EventSubscriber.h"

namespace MahatmaGameEngine
{
	typedef std::chrono::high_resolution_clock::time_point TimePoint;
	typedef std::chrono::milliseconds MilliSeconds;
	typedef std::chrono::high_resolution_clock Clock;

	class EventPublisher abstract : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)
	public:
		/**
		* Constructor of the EventPublisher requires an address to a list of subscribers and whether to delete the event after publishing.
		* @param subscriberList is the Vector of EventSubscriber addresses
		* @param deleteAfter bool value that states whether this event will be deleted after publishing.
		*/
		EventPublisher(Vector<EventSubscriber*>& subscriberList);

		/**
		* Copy constructor of EventPublisher constructs a copy of the EventPublisher passed as parameter.
		* @param obj EventPublisher reference to the object to be copied from.
		*/
		EventPublisher(const EventPublisher& obj);

		/**
		* Move constructor of EventPublisher constructs a shallow copy of the EventPublisher passed as parameter.
		* @param obj EventPublisher rValue reference to the object to be copied from.
		*/
		EventPublisher(EventPublisher&& obj);

		/**
		* Default destructor of EventPublisher
		*/
		virtual ~EventPublisher() = default;

		/**
		* Assignment operator to deep copy from another EventPublisher
		* @param obj EventPublisher reference to the object to copy from.
		* @return EventPublisher reference to this.
		*/
		EventPublisher& operator=(const EventPublisher& obj);

		/**
		* Assignment operator to move from an rValue EventPublisher
		* @param obj EventPublisher rValue reference to the object to move.
		* @return EventPublisher reference to this. 
		*/
		EventPublisher& operator=(EventPublisher&& obj);

		/**
		* Sets the time constraints for the event.
		* @param time the high_resolution_clock::time_point reference at which the event is enqueued.
		* @param delay the time in milliseconds with which to delay the event being published.
		*/
		void setTime(const TimePoint& time, const MilliSeconds& delay = MilliSeconds(0));
		
		/**
		* Returns the time at which the event was enqueued.
		* @return TimePoint reference to the time at which the event was enqueued.
		*/
		TimePoint& timeEnqueued();
		
		/**
		* Check if the event delay timer has expired.
		* @param currentTime the current time at time of function call.
		* @return returns true if the delay time has expired.
		*/
		bool isExpired(const TimePoint& currentTime);
		
		/**
		* Calls the notify method on all of the EventSubscribers in the list.
		*/
		void deliver();

	private:
		TimePoint mTimeEnqueued;				/**< The time at which the event was enqueued. */
		MilliSeconds mDelay;					/**< The delay after which the event will be published. */
		Vector<EventSubscriber*>* mSubscribers;	/**< The list of subscribers to this event. */
	};
}
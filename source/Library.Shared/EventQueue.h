#pragma once
#include "Vector.h"
#include "EventPublisher.h"
#include <memory>

namespace MahatmaGameEngine
{
	class GameTime;

	class EventQueue final
	{
	public:
		/**
		* Default constructor of EventQueue class
		*/
		EventQueue() = default;

		/**
		* Default destructor of EventQueue
		*/
		~EventQueue() = default;

		EventQueue(const EventQueue&) = delete;
		EventQueue(EventQueue&&) = delete;

		/**
		* Queues the event in the EventQueue and sets the time at which it was enqueued and the delay till event is fired.
		* @param event the shared_ptr to the EventPublisher base class. This is the event to enqueue.
		* @param time the GameTime object that contains the currentTime and such attributes.
		* @param delay the delay in milliseconds before the event is fired.
		*/
		void enqueue(std::shared_ptr<EventPublisher> event, const GameTime& time, const MilliSeconds& delay = MilliSeconds(0));

		/**
		* Lightly wrapped method to expose the deliver call of the event via EventQueue.
		* @param event to call the deliver on.
		*/
		void send(EventPublisher& event);

		/**
		* Update call that delivers the events that are expired and removes them from the queue.
		* @param time the GameTime used to determine if the events have expired.
		*/
		void update(const GameTime& time);

		/**
		* If parameter true is passed, the expired events are delivered and then clears the queue.
		* @param sendExpired if true, the method delivers the events. False by default.
		*/
		void clear(bool sendExpired = false);

		/**
		* Query to check if the queue is empty.
		* @return true if empty.
		*/
		bool isEmpty();

		/**
		* Query to check the size of the queue.
		* @return uint32_t of the size of the queue.
		*/
		std::uint32_t size();
	private:
		/**
		* Creates a partition of all the expired events and then sends them before dequeuing them.
		* @param timePoint the TimePoint at which the expiry of events needs to be checked.
		*/
		void sendExpiredEvents(const TimePoint& timePoint);

		Vector<std::shared_ptr<EventPublisher>> mEventQueue;		/**< The vector that queues the events. */
		std::recursive_mutex mMutex;
	};
}
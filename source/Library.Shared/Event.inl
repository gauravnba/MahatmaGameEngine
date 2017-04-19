#pragma once

namespace MahatmaGameEngine
{
	template <typename T>
	Vector<EventSubscriber*> Event<T>::mSubscribers;

	template <typename T>
	Event<T>::Event(const T& eventMessage) :
		mPayload(eventMessage), EventPublisher(mSubscribers)
	{
	}

	template <typename T>
	Event<T>::Event(const Event<T>& obj) :
		mPayload(obj.mPayload), EventPublisher(obj)
	{
	}

	template <typename T>
	Event<T>::Event(Event<T>&& obj) :
		mPayload(obj.mPayload), EventPublisher(move(obj))
	{
	}

	template<typename T>
	Event<T>& Event<T>::operator=(const Event<T>& obj)
	{
		if (this != &obj)
		{
			mPayload = obj.mPayload;
			EventPublisher::operator=(obj);
		}
		return *this;
	}

	template<typename T>
	Event<T>& Event<T>::operator=(Event<T>&& obj)
	{
		if (this != &obj)
		{
			mPayload = obj.mPayload;
			EventPublisher::operator=(move(obj));
		}
		return *this;
	}

	template<typename T>
	void Event<T>::subscribe(const EventSubscriber& subscriber)
	{
		mSubscribers.pushBack(&(const_cast<EventSubscriber&>(subscriber)));
	}

	template<typename T>
	void Event<T>::unsubscribe(const EventSubscriber& subscriber)
	{
		mSubscribers.remove(&(const_cast<EventSubscriber&>(subscriber)));
	}

	template<typename T>
	void Event<T>::unsubscribeAll()
	{
		mSubscribers.clear();
	}

	template<typename T>
	const T& Event<T>::message() const
	{
		return mPayload;
	}
}
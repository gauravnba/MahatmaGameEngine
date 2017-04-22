#pragma once

namespace MahatmaGameEngine
{
	template <typename T>
	Vector<EventSubscriber*> Event<T>::mSubscribers;

	template <typename T>
	std::mutex Event<T>::mMutex;

	template <typename T>
	Event<T>::Event(const T& eventMessage) :
		mPayload(eventMessage), EventPublisher(mSubscribers, mMutex)
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
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.pushBack(&(const_cast<EventSubscriber&>(subscriber)));
	}

	template<typename T>
	void Event<T>::unsubscribe(const EventSubscriber& subscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.remove(&(const_cast<EventSubscriber&>(subscriber)));
	}

	template<typename T>
	void Event<T>::unsubscribeAll()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.clear();
	}

	template<typename T>
	const T& Event<T>::message() const
	{
		return mPayload;
	}
}
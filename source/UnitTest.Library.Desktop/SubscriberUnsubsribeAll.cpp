#include "pch.h"
#include "SubscriberUnsubsribeAll.h"

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;

void SubscriberUnsubscribeAll::notify(const MahatmaGameEngine::EventPublisher& subscribedTo)
{
	UNREFERENCED_PARAMETER(subscribedTo);
	Event<Foo>::unsubscribeAll();
}
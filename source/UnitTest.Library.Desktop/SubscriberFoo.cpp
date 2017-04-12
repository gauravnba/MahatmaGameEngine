#include "pch.h"

#include "SubscriberFoo.h"
#include "Event.h"

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;
using namespace std;

SubscriberFoo::SubscriberFoo() :
	mValue(0)
{
}

void SubscriberFoo::notify(const EventPublisher& publisher)
{
	assert(publisher.is(Event<Foo>::typeIdClass()));
	Foo foo = static_cast<const Event<Foo>&>(publisher).message();

	mValue = foo.getVar() + mValue;
}

uint32_t SubscriberFoo::getValue()
{
	return mValue;
}

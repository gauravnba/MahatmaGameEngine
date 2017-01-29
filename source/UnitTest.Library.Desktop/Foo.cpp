#include "pch.h"

#include "Foo.h"

using namespace UnitTestLibraryDesktop;

Foo::Foo()
{
	mVar = new std::uint32_t(0);
}

Foo::Foo(std::uint32_t data)
{
	mVar = new std::uint32_t(data);
}

Foo::Foo(const Foo& obj)
{
	mVar = new std::uint32_t;
	*mVar = *(obj.mVar);
}

Foo::~Foo()
{
	delete mVar;
}

Foo& Foo::operator=(const Foo& obj)
{
	*mVar = *(obj.mVar);
	return *this;
}

bool Foo::operator==(const Foo& obj) const
{
	return (*mVar == *(obj.mVar));
}

bool Foo::operator!=(const Foo& obj) const
{
	return !(*this == obj);
}

std::uint32_t Foo::getVar() const
{
	return *mVar;
}
#pragma once
#include <cstdint>
class Foo
{
public:
	Foo();
	Foo(std::uint32_t data);
	~Foo();
	Foo(const Foo& obj);
	Foo& operator= (const Foo& obj);
	bool operator== (const Foo& obj) const;
	std::uint32_t getVar() const;

private:
	std::uint32_t* mVar;
};
#include "pch.h"

#include "FooDefaultHash.h"

using namespace MahatmaGameEngine;

std::uint32_t DefaultHash<Foo>::operator()(const Foo& key)
{
	std::int32_t* keyCopy = new int32_t(key.getVar());
	const char* keyValue = reinterpret_cast<const char*>(keyCopy);

	std::uint32_t i = 0;

	//prime factor to hash. Value used is based on pre-existing tests.
	const std::uint32_t prime = 0x01000193;
	std::uint32_t hashVal = 0x811C9DC5;

	while (i < sizeof(keyValue))
	{
		hashVal = (keyValue[i++] ^ hashVal) * prime;
	}
	delete keyCopy;

	return hashVal;
}
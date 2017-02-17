#include "pch.h"

#include <cstring>
#include "DefaultHash.h"

using namespace MahatmaGameEngine;

std::uint32_t DefaultHash<char*>::operator()(const char* key)
{
	std::uint32_t length = strlen(key);

	//prime factor to hash. Value used is based on pre-existing tests.
	const std::uint32_t prime = 0x01000193;
	std::uint32_t hashVal = 0x811C9DC5;

	while (length--)
	{
		hashVal = (*key++ ^ hashVal) * prime;
	}
	return hashVal;
}

std::uint32_t DefaultHash<std::string>::operator()(const std::string& key)
{
	std::uint32_t length = static_cast<uint32_t>(key.size());
	char* keyVal = const_cast<char*>(key.c_str());

	//prime factor to hash. Value used is based on pre-existing tests.
	const std::uint32_t prime = 0x01000193;
	std::uint32_t hashVal = 0x811C9DC5;

	while (length--)
	{
		hashVal = (*keyVal++ ^ hashVal) * prime;
	}
	return hashVal;
}
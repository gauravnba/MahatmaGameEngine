#pragma once

namespace MahatmaGameEngine
{
	template <typename T>
	std::uint32_t DefaultHash<T>::operator()(const T& key)
	{
		const char* keyValue = reinterpret_cast<const char*>(&key);

		std::uint32_t i = 0;

		//prime factor to hash. Value used is based on pre-existing tests.
		const std::uint32_t prime = 0x01000193;
		std::uint32_t hashVal = 0x811C9DC5;

		while (i < sizeof(T))
		{
			hashVal = (keyValue[i++] ^ hashVal) * prime;
		}
		return hashVal;
	}
}
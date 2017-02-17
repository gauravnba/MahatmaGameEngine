#pragma once

#include <cstdint>
#include <exception>
#include <string>

namespace MahatmaGameEngine
{
	template <typename T>
	class DefaultHash
	{
	public:
		/**
		* Operator() overload to allow the class to be used as a functor.
		* @param key of templated type required to compute the hash.
		* @return unsigned int value of the computed hash.
		*/
		std::uint32_t operator()(const T& key);
	};

	template <>
	class DefaultHash <char*>
	{
	public:
		/**
		* Operator() overload to allow the class to be used as a functor.
		* @param key of primitive string type required to compute the hash.
		* @return unsigned int value of the computed hash.
		*/
		std::uint32_t operator()(const char* key);
	};

	template <>
	class DefaultHash <std::string>
	{
	public:
		/**
		* Operator() overload to allow the class to be used as a functor.
		* @param key of standard string type required to compute the hash.
		* @return unsigned int value of the computed hash.
		*/
		std::uint32_t operator()(const std::string& key);
	};
}

#include "DefaultHash.inl"
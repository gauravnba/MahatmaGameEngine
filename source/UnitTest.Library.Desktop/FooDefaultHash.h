#pragma once
#include "Foo.h"
#include "DefaultHash.h"

using namespace UnitTestLibraryDesktop;
namespace MahatmaGameEngine
{
	template <>
	class DefaultHash<Foo>
	{
	public:
		/**
		* Default constructor for the DefaultHash.
		*/
		DefaultHash() = default;

		/**
		* Default destructor for the DefaultHash.
		*/
		~DefaultHash() = default;

		/**
		* Operator() overload to allow the class to be used as a functor.
		* @param key of primitive string type required to compute the hash.
		* @return unsigned int value of the computed hash.
		*/
		std::uint32_t operator()(const Foo& key);
	};
}
#pragma once

#include "RTTI.h"
#include "Factory.h"
#include <cstdint>

namespace UnitTestLibraryDesktop
{	
	class FooProduct : public MahatmaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(FooProduct, MahatmaGameEngine::RTTI)
	public:
		void setProductValue(std::uint32_t value);

		std::int32_t getProductValue();

	private:
		std::int32_t mProductValue;
	};

	CONCRETE_FACTORY(MahatmaGameEngine::RTTI, FooProduct)
}
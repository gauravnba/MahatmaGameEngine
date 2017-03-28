#pragma once

#include "Factory.h"
#include <cstdint>

namespace UnitTestLibraryDesktop
{
	class BarProductAbstract
	{
	public:
		virtual void setProductValue(std::int32_t value) = 0;
	};

	class BarProduct : public BarProductAbstract
	{
	public:
		virtual void setProductValue(std::int32_t value) override;

		std::int32_t getProductValue();
	private:
		std::int32_t mProductValue;
	};

	CONCRETE_FACTORY(BarProductAbstract, BarProduct)
}
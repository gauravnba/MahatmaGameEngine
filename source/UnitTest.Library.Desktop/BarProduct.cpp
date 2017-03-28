#include "pch.h"
#include "BarProduct.h"

void UnitTestLibraryDesktop::BarProduct::setProductValue(std::int32_t value)
{
	mProductValue = value;
}

std::int32_t UnitTestLibraryDesktop::BarProduct::getProductValue()
{
	return mProductValue;
}

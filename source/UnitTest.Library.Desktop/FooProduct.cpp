#include "pch.h"

#include "FooProduct.h"

using namespace UnitTestLibraryDesktop;
//using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(FooProduct)

void FooProduct::setProductValue(std::uint32_t value)
{
	mProductValue = value;
}

std::int32_t FooProduct::getProductValue()
{
	return mProductValue;
}
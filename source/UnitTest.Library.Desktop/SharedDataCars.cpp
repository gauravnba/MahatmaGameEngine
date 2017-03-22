#include "pch.h"

#include "SharedDataCars.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(SharedDataCars)

void SharedDataCars::initialize()
{
	SharedData::initialize();
	mFoundAttributes.clear();
}

XMLParseMaster::SharedData* SharedDataCars::clone()
{
	return new SharedDataCars;
}
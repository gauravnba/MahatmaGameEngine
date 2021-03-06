#include "pch.h"

#include "SharedDataMotorcycles.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(SharedDataMotorcycles)

void SharedDataMotorcycles::initialize()
{
	SharedData::initialize();
	mFoundAttributes.clear();
}

XMLParseMaster::SharedData* SharedDataMotorcycles::clone()
{
	return new SharedDataMotorcycles;
}
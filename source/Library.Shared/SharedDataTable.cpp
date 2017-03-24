#include "pch.h"

#include "SharedDataTable.h"

using namespace MahatmaGameEngine;

RTTI_DEFINITIONS(SharedDataTable)

void SharedDataTable::initialize()
{
	SharedData::initialize();
	mSharedTable.clear();
}

XMLParseMaster::SharedData* SharedDataTable::clone()
{
	return new SharedDataTable;
}
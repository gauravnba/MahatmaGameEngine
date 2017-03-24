#include "pch.h"

#include "SharedDataTable.h"

using namespace MahatmaGameEngine;

RTTI_DEFINITIONS(SharedDataTable)

SharedDataTable::SharedDataTable() :
	mCurrentTable(new Scope)
{
}

void SharedDataTable::initialize()
{
	SharedData::initialize();
	mCurrentTable->clear();
}

XMLParseMaster::SharedData* SharedDataTable::clone()
{
	return new SharedDataTable;
}

bool SharedDataTable::equals(const RTTI* rhs) const
{
	return (mCurrentTable->equals(rhs->as<SharedDataTable>()->mCurrentTable));
}
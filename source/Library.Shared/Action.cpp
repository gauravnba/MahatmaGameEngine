#include "pch.h"

#include "Action.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Action)

void Action::setName(const std::string& name)
{
	mName = name;
}

string& Action::name()
{
	return mName;
}
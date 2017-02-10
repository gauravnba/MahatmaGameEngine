#include "Datum.h"

using namespace MahatmaGameEngine;
using namespace std;

Datum::Datum() :
	mSize(0), mCapacity(0)
{
}

Datum::~Datum()
{
	clear();
}

Datum::Datum(const Datum& obj) :
	mSize(obj.mSize), mCapacity(obj.mCapacity)
{
}

DatumType MahatmaGameEngine::Datum::type() const
{
	return mType;
}


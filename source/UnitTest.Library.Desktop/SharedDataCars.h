#pragma once

#include "XMLParseMaster.h"
#include "RTTI.h"
#include "Hashmap.h"

namespace UnitTestLibraryDesktop
{
	class SharedDataCars : public MahatmaGameEngine::XMLParseMaster::SharedData
	{
		RTTI_DECLARATIONS(SharedDataCars, MahatmaGameEngine::XMLParseMaster::SharedData)
	public:
		SharedDataCars() = default;

		virtual ~SharedDataCars() = default;

		virtual void initialize();

		virtual SharedData* clone() override;

		MahatmaGameEngine::Scope mFoundAttributes;
	};
}
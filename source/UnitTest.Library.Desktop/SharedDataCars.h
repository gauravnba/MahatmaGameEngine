#pragma once

#include "XMLParseMaster.h"
#include "RTTI.h"
#include "Scope.h"

namespace UnitTestLibraryDesktop
{
	class SharedDataCars : public MahatmaGameEngine::XMLParseMaster::SharedData
	{
		RTTI_DECLARATIONS(SharedDataCars, MahatmaGameEngine::XMLParseMaster::SharedData)
	public:
		SharedDataCars() = default;

		virtual ~SharedDataCars() = default;

		virtual void initialize();

		virtual XMLParseMaster::SharedData* clone() override;

		MahatmaGameEngine::Scope mFoundAttributes;
	};
}
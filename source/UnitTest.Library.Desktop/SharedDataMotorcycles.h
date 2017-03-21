#pragma once

#include "XMLParseMaster.h"
#include "RTTI.h"

namespace UnitTestLibraryDesktop
{
	class SharedDataMotorcycles : public MahatmaGameEngine::XMLParseMaster::SharedData
	{
		RTTI_DECLARATIONS(SharedDataMotorcycles, MahatmaGameEngine::XMLParseMaster::SharedData)
	public:
		SharedDataMotorcycles() = default;

		virtual ~SharedDataMotorcycles() = default;

		virtual void initialize();

		virtual SharedData* clone() override;
	};
}
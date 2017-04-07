#pragma once

#include "Action.h"
#include "Factory.h"

namespace UnitTestLibraryDesktop
{
	struct MahatmaGameEngine::WorldState;

	class ActionFoo : public MahatmaGameEngine::Action
	{
		RTTI_DECLARATIONS(ActionFoo, Action)
	public:
		ActionFoo();

		virtual ~ActionFoo() = default;

		std::uint32_t getCounterValue();

		virtual void update(MahatmaGameEngine::WorldState& worldState) override;

	private:
		std::uint32_t mUpdateCounter;
	};
	
	CONCRETE_FACTORY(MahatmaGameEngine::Action, ActionFoo)
}
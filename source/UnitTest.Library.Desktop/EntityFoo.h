#pragma once

#include "Factory.h"
#include "Entity.h"
#include <cstdint>

namespace UnitTestLibraryDesktop 
{
	struct MahatmaGameEngine::WorldState;

	class EntityFoo : public MahatmaGameEngine::Entity
	{
		RTTI_DECLARATIONS(EntityFoo, MahatmaGameEngine::Entity)

	public:
		EntityFoo();

		virtual ~EntityFoo() = default;

		std::uint32_t getCounterValue();

		virtual void update(MahatmaGameEngine::WorldState& worldState) override;

	private:
		std::uint32_t mCounter;
	};

	CONCRETE_FACTORY(MahatmaGameEngine::Entity, EntityFoo)
}
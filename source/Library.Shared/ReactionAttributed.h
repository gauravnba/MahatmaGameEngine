#pragma once

#include "Reaction.h"
#include "Factory.h"

namespace MahatmaGameEngine
{
	class ReactionAttributed : public Reaction
	{
	public:

		ReactionAttributed();

		virtual ~ReactionAttributed() = default;

		virtual void notify(const EventPublisher& subscribedTo) override;
	};

	CONCRETE_FACTORY(Reaction, ReactionAttributed)
}
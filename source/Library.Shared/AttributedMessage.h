#pragma once

#include "Attributed.h"

namespace MahatmaGameEngine
{
	struct WorldState;

	class AttributedMessage : public Attributed
	{
		RTTI_DECLARATIONS(AttributedMessage, Attributed)
	public:
		AttributedMessage();

		AttributedMessage(const std::string& subType, WorldState& worldState);

		AttributedMessage(const AttributedMessage& obj);

		virtual ~AttributedMessage() = default;

		AttributedMessage& operator=(const AttributedMessage& obj);

		void setSubType(const std::string& subType);

		std::string& getSubType();

		const std::string& getSubType() const;

		void setWorldState(WorldState& worldState);

		WorldState& getWorldState();
	private:
		void populatePrescribed();

		std::string mSubType;
		WorldState* mWorldState;
	};
}
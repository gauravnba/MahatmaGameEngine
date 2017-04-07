#pragma once

#include "Action.h"

namespace MahatmaGameEngine
{
	class ActionSetString : public Action
	{
	public:
		ActionSetString();

		virtual ~ActionSetString() = default;

		void setName(const std::string& name);

		void setStringValues(const std::string& stringToChange, const std::string& value);

		virtual void update(WorldState& worldState) override;
	private:
		std::string mName;
		std::string mString;
		std::string mStringValue;
	};

	ACTION_FACTORY(ActionSetString)
}
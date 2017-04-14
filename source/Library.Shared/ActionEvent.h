#pragma once

#include "Action.h"

namespace MahatmaGameEngine
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)
	public:
		/**
		* 
		*/
		ActionEvent();

		virtual ~ActionEvent() = default;

		virtual void update(WorldState& worldState) override;

		void setAttributes(const std::string& subType, std::uint32_t delay);

		void setSubType(const std::string& subType);

		const std::string& getSubType() const;

		std::string& getSubType();

		void setDelay(std::uint32_t delay);

		std::uint32_t getDelay();

	private:
		std::string mSubType;
		std::int32_t mDelay;
	};

	CONCRETE_FACTORY(Action, ActionEvent)
}
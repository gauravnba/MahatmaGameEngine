#pragma once

#include "Action.h"

namespace MahatmaGameEngine
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)
	public:
		/**
		* ActionEvent constructor populates the prescribed attributes of the class.
		*/
		ActionEvent();

		/**
		* Default destructor of ActionEvent.
		*/
		virtual ~ActionEvent() = default;

		/**
		* Virtual implementation of the Action update. Creates an attributed event, 
		assign its world and subtype, copy all auxiliary parameters into the event and queue the event with the given delay.
		* @param worldState the WorldState of the system currently.
		*/
		virtual void update(WorldState& worldState) override;

		/**
		* Mutator for the member variables of the class.
		* @param subType sets the value of the subType of the class.
		* @param delay of time before the event will be notified.
		*/
		void setAttributes(const std::string& subType, std::uint32_t delay);

		/**
		* Mutator for the sub type of the class.
		* @param subType value to set the sub type to.
		*/
		void setSubType(const std::string& subType);

		/**
		* Const Accessor of the sub type of the class.
		* @return the string value of sub type.
		*/
		const std::string& getSubType() const;

		/**
		* Accessor of the sub type of the class.
		* @return the string value of sub type.
		*/
		std::string& getSubType();

		/**
		* Mutator for the delay of the event created by the class.
		* @param delay the unsigned integer value to set the delay to.
		*/
		void setDelay(std::uint32_t delay);

		/**
		* Accessor of delay that the event of this class will generate.
		* @return the unsigned int value of the delay.
		*/
		std::uint32_t getDelay();

	private:
		std::string mSubType;	/**< The sub type of the class. */
		std::int32_t mDelay;	/**< The delay to set the class to. */
	};

	CONCRETE_FACTORY(Action, ActionEvent)
}
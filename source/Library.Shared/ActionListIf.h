#pragma once

#include "ActionList.h"
#include <cstdint>

namespace MahatmaGameEngine
{
	/**
	* This ActionList processes an if condition and calls the update method of any actions in it.
	*/
	class ActionListIf : public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf, ActionList)
	public:
		/**
		* Default constructor of the class sets the attributes.
		*/
		ActionListIf();

		/**
		* Default destructor of the class.
		*/
		virtual ~ActionListIf() = default;

		/**
		* Sets the value of the condition for this if block
		* @param condition the value of the condition
		*/
		void setCondition(const std::string& condition);

		Action& createAction(const std::string& className, const std::string& instanceName, bool isThenAction);

		/**
		* The update override of this derived class
		* @param worldState the state of the world at the current time.
		*/
		virtual void update(WorldState& worldState) override;

	private:
		std::string mCondition;		/**< The name of the datum to resolve for the condition. */
	};

	ACTION_FACTORY(ActionListIf)
}
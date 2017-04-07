#pragma once

#include "Action.h"
#include "Scope.h"

namespace MahatmaGameEngine
{
	/**
	* To allow a list of Actions in an Action.
	*/
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)
	public:
		/**
		* Default constructor sets the attributed scope of the class.
		*/
		ActionList();

		/**
		* Default constructor for ActionList.
		*/
		virtual ~ActionList() = default;

		/**
		* Creates an action and adopts it into the actions Datum.
		* @param className the name of the class that the instance will be of.
		* @param instanceName the name attribute of the Action created.
		* @return Action reference to the created Action.
		*/
		Action& createAction(const std::string& className, const std::string& instanceName);

		/**
		* Update method implementation for the ActionList.
		* @param worldState is the state of the world at the current time.
		*/
		virtual void update(WorldState& worldState) override;
	};

	ACTION_FACTORY(ActionList)
}
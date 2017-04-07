#pragma once

#include "Action.h"
#include <string>

namespace MahatmaGameEngine
{
	/**
	* This class is used to destroy a created action.
	*/
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action)
	public:
		/**
		* Constructor of ActionDestroyAction sets the attributes of the class
		*/
		ActionDestroyAction();

		/**
		* Constructor of ActionDestroyAction sets the attributes of the class
		* @param name of the class to delete.
		*/
		ActionDestroyAction(const std::string& name);

		/**
		* Default destructor of the class
		*/
		virtual ~ActionDestroyAction() = default;

		/**
		* Set the name of the action class to destroy.
		* @param actionName is the name of the action class to destroy.
		*/
		void setAction(const std::string& actionName);

		/**
		* Concrete implementation of the update method of the Action class. Destroys action of the action attribute of class.
		* @param worldState the current WorldState at the time of update call.
		*/
		virtual void update(WorldState& worldState) override;
	private:
		std::string mAction;		/**< The action that the destroy call is supposed to delete. */
	};

	ACTION_FACTORY(ActionDestroyAction)
}
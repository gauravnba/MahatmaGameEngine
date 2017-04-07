#pragma once

#include "Action.h"

namespace MahatmaGameEngine
{
	/**
	* This action is used to create a new Action and adopt it to the parent.
	*/
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action)
	public:
		/**
		* The constructor of the ActionCreateAction class that populates the attributes map.
		*/
		ActionCreateAction();

		/**
		* The constructor of the ActionCreateAction class that populates the attributes map.
		* @param name to set the mName parameter.
		* @param prototype to set the mPrototype parameter.
		*/
		ActionCreateAction(const std::string& name, const std::string& prototype);

		/**
		* Default destructor of ActionCreateAction.
		*/
		virtual ~ActionCreateAction() = default;

		/**
		* Sets the properties for the action class to create.
		* @param name for the name of the Action created.
		* @prototype name of the class to create.
		*/
		void setPropertiesForAction(const std::string& name, const std::string& prototype);

		/**
		* Creates an action of type of the prototype attribute and name of name attribute.
		* @param worldState the state of the world at the time of calling.
		*/
		virtual void update(WorldState& worldState) override;

	private:
		std::string mName;			/**< The name of the name attribute of the action object to create. */
		std::string mPrototype;		/**< The name of the type of the class to create. */
	};

	ACTION_FACTORY(ActionCreateAction)
}
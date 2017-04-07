#pragma once

#include "Attributed.h"
#include "Factory.h"
#include <string>

namespace MahatmaGameEngine
{
	struct WorldState;

	/**
	* Action Interface that all actions will be derived from.
	*/
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)
	
	public:
		/**
		* Default destructor for Action class.
		*/
		virtual ~Action() = default;

		/**
		* Sets the value of the name attribute of Action instance.
		* @param name the value of the name attribute of this class to set to.
		*/
		void setName(const std::string& name);

		/**
		* The value of the name attribute of this action.
		* @return the string value of name attribute.
		*/
		std::string& name();

		/**
		* The pure virtual update method that the derived classes implement.
		* @param worldState the current state of the world at the current time.
		*/
		virtual void update(WorldState& worldState) = 0;

	protected:
		std::string mName;		/**< The name attribute value of the Action class */
	};
}

#define ACTION_FACTORY(ActionDerived)			\
	CONCRETE_FACTORY(Action, ActionDerived)
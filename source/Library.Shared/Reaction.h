#pragma once

#include "ActionList.h"
#include "EventSubscriber.h"

namespace MahatmaGameEngine
{
	/**
	* The Reaction abstract class ties the Actions and Events systems together.
	*/
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)
	public:
		/**
		* The default destructor for Reaction.
		*/
		virtual ~Reaction() = default;

	protected:
		Reaction() = default;
	};
}
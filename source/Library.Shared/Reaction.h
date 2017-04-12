#pragma once

#include "ActionList.h"
#include "EventSubscriber.h"

namespace MahatmaGameEngine
{
	/**
	* The Reaction abstract class ties the Actions and Events systems together.
	*/
	class Reaction abstract: public ActionList, public EventSubscriber
	{
	public:
		/**
		* The default destructor for Reaction.
		*/
		virtual ~Reaction() = default;
	};
}
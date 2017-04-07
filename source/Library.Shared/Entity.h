#pragma once

#include "Attributed.h"
#include <string>
#include "Factory.h"

namespace MahatmaGameEngine
{
	struct WorldState;
	class Sector;

	/**
	* An Entity is a Game Object that holds Actions (verbs)
	*/
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		/**
		* Constructor of Entity constructs the object and then assigns its default values to Attributed.
		*/
		Entity();

		/**
		* Move constructor of Entity invokes the move constructor of Attributed.
		* @param obj the Entity object to move.
		*/
		Entity(Entity&& obj);

		/**
		* Default destructor of Entity.
		*/
		virtual ~Entity() = default;

		/**
		* Move Assignment operator for Entity invokes the Attributed move assignment.
		* @param obj the Entity object to move.
		* @return this Entity that obj was moved to.
		*/
		Entity& operator=(Entity&& obj);

		/**
		* Sets the value of the name Attribute of Entity.
		* @param name string value of the new Entity name.
		*/
		void setName(const std::string& name);

		/**
		* Accessor for the name attribute of the Entity.
		* @return string value of the Entity name.
		*/
		std::string& name();

		/**
		* Accessor for the parent Sector of this Entity.
		* @return address of the parent Sector
		*/
		Sector* getSector();

		/**
		* Creates an action and adopts it into the actions Datum.
		* @param className the name of the class that the instance will be of.
		* @param instanceName the name attribute of the Action created.
		* @return Action reference to the created Action.
		*/
		Action& createAction(const std::string& className, const std::string& instanceName);

		/**
		* Update method called every frame in the game loop. This method is invoked by the Parent Sector.
		* The update method in the child Entities should be accessible via this method, hence it is marked virtual.
		* @param worldState the current WorldState.
		*/
		virtual void update(WorldState& worldState);

	private:
		std::string mName;				/**< The name attribute of the Entity. */
	};

	CONCRETE_FACTORY(Entity, Entity)
}
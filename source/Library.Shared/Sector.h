#pragma once

#include "Attributed.h"

namespace MahatmaGameEngine
{
	class World;
	class Entity;
	struct WorldState;

	/**
	* A Sector is another container, but it is one which does not introduce a namespace.
	* We should be able to move data and processes between Sectors without affecting anything in the data itself.
	*/
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		/**
		* Sector constructor assigns the default value to Attributed.
		*/
		Sector();

		/**
		* Sector constructor overload that assigns the mName with the string parameter passed.
		* @param name value to assign the name attribute with.
		* @overlaod Sector();
		*/
		Sector(const std::string& name);

		/**
		* Disallow copy construction of Sector. 
		*/
		Sector(const Sector& obj) = delete;

		/**
		* Disallow move construction of Sector.
		*/
		Sector(Sector&& obj) = delete;

		/**
		* Default destructor of Sector declared virtual.
		*/
		virtual ~Sector() = default;

		/**
		* Accessor for the Datum of entities held by the Sector.
		* @return the Datum reference of the entities in the Sector.
		*/
		Datum& entities();

		/**
		* Mutator of name attribute of Sector.
		* @param name the value to set the name attribute to.
		*/
		void setName(const std::string& name);

		/**
		* Accessor of the name attribute of Sector.
		* @return string value reference of the name of this Sector.
		*/
		std::string& name();

		/**
		* Creates an entity using the Entity Factory of the className passed.
		* Please note that the Factory should already be existent when a call to createEntity is made.
		* @param className is the name of the product class that the factory belongs to.
		* @param instanceName is the value that will be assigned to the name attribute of the created Factory.
		* @return Returns an Entity reference to the one just created.
		*/
		Entity& createEntity(const std::string& className, const std::string& instanceName);

		/**
		* Creates an action and adopts it to the Sector.
		* @param actionName name of the action class to define.
		* @param instanceName name of the action.
		* @return Action reference to the created Action.
		*/
		Action& createAction(const std::string& actionName, const std::string& instanceName);

		/**
		* Adopts an Entity that does not currently belong to this Sector.
		* @param entity the Entity object to be adopted to Sector.
		*/
		void adoptEntity(Entity& entity);

		/**
		* Accessor for the parent World of this Sector.
		* @return Address of the World that this object belongs to.
		*/
		World* getWorld();

		/**
		* Update method called by the gameloop via the World object.
		* @param worldState the current state of the world.
		*/
		void update(WorldState& worldState);

	private:

		/**
		* This is a helper method used by the Constructor to populate the Attributed Scope at construction.
		*/
		void populateAttributed();

		std::string mName;				/**< The value of the name attribute of this Sector. */
	};
}
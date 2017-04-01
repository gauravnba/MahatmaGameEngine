#pragma once

#include "Attributed.h"
#include <string>

namespace MahatmaGameEngine
{
	class Sector;
	struct WorldState;

	/**
	* World is a container for an interactive simulation. 
	* It defines a global scope, contains a list of Sectors and an event queue.
	*/
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		/**
		* Default constructor that populates the Attributed Scope of this World.
		*/
		World();

		/**
		* Overloads the default constructor of the World class by setting the name attribute on construction.
		* @param name the string value to be assigned to the name attribute.
		*/
		World(const std::string& name);

		/**
		* Move constructor copies the name attribute and invokes the move constructor of the Attributed.
		* @param obj the World object to move from.
		*/
		World(World&& obj);

		/**
		* Virtual default destructor of the World class.
		*/
		virtual ~World() = default;

		/**
		* Move assignment operator invokes the move assignment operator of Attributed.
		* @param obj the World object to move from.
		*/
		World& operator=(World&& obj);

		/**
		* Accessor of the name attribute of World.
		* @return string value of the name attribute.
		*/
		std::string& name();

		/**
		* Mutator of the name attribute of the World
		* @param name the value to set the name attribute to.
		*/
		void setName(const std::string& name);

		/**
		* Accessor of the sectors contained within this World.
		* @return Datum reference to the sectors entry in this Scope.
		*/
		Datum& sectors();

		/**
		* Creates a new sector in this World and allows access to it.
		* @return Sector reference to the created Sector.
		*/
		Sector& createSector();

		/**
		* Overload for createSector that creates the Sector with the given name attribute value.\
		* @param sectorName the value with which to name the Sector.
		* @return Sector reference to the created Sector.
		* @overload createSector();
		*/
		Sector& createSector(const std::string& sectorName);

		/**
		* Update method called by the gameloop to update the world and all its children.
		* @param worldState the current World, Sector and Entity that the update is in, along with GameTime.
		*/
		void update(WorldState& worldState);

	private:
		/**
		* This is a helper method used by the Constructor to populate the Attributed Scope at construction.
		*/
		void populateAttributed();

		std::string mName;			/**< The name assigned to the World. */
	};
}
#pragma once

#include "Attributed.h"

namespace MahatmaGameEngine
{
	struct WorldState;

	class AttributedMessage : public Attributed
	{
		RTTI_DECLARATIONS(AttributedMessage, Attributed)
	public:
		/**
		* Default Constructor for AttributedMessage populates the Attributed Scope with the subType of the class.
		*/
		AttributedMessage();

		/**
		* Constructor that populates the Attributed Scope with the subType and also sets the values of subType and worldState.
		* @param subType of the class that is used to check with the Reaction to check if this is the message intended for the reaction.
		* @param worldState being used by the system.
		*/
		AttributedMessage(const std::string& subType, WorldState& worldState);

		/**
		* Copy constructor of AttributedMessage.
		* @param obj the object to copy from.
		*/
		AttributedMessage(const AttributedMessage& obj);

		/**
		* Default destructor of AttributedMessage.
		*/
		virtual ~AttributedMessage() = default;

		/**
		* Copy assignment operator for AttributedMessage.
		* @param obj the object to copy from.
		*/
		AttributedMessage& operator=(const AttributedMessage& obj);

		/**
		* Mutator for the sub type of the class.
		* @param subType the string value to set the sub type to.
		*/
		void setSubType(const std::string& subType);

		/**
		* Accessor for the string sub type.
		* @return string type value of subType.
		*/
		std::string& getSubType();

		/**
		* Const version of getSubType.
		* @return string type value of subType.
		*/
		const std::string& getSubType() const;

		/**
		* Sets the WorldState that will be used by the class.
		* @param worldState value of the WorldState to set to.
		*/
		void setWorldState(WorldState& worldState);

		/**
		* Accessor for the WorldState used by this class.
		* @return WorldState being used by this class.
		*/
		WorldState& getWorldState();
	private:
		/**
		* Populates the Attributed Scope with the prescribed attributes of the class.
		*/
		void populatePrescribed();

		std::string mSubType;		/**< The sub type of the class. */
		WorldState* mWorldState;	/**< The WorldState being used by the class. Used as a component of the message itself. */
	};
}
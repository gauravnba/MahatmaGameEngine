#pragma once

#include "Reaction.h"
#include "Factory.h"

namespace MahatmaGameEngine
{
	/**
	* ReactionAttributed is a type of Reaction that implements the notify virtual method from EventSubscriber.
	*/
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)
	public:
		/**
		* Default constructor of ReactionAttributed, subscribes to Events of type EventMessageAttributed.
		*/
		ReactionAttributed();

		/**
		* Default destructor of ReactionAttributed unsubscribes from the Events of type EventMessageAttributed.
		*/
		virtual ~ReactionAttributed();

		/**
		* Notify virtual method captures an Event of EventMessageAttributed and copies the message. It then calls the ActionList::update()
		* @param subscribedTo is the event of EventMessageAttributed that this object had subscribed to.
		*/
		virtual void notify(const EventPublisher& subscribedTo) override;

		/**
		* Mutator for subType.
		* @param subType string type value to assign of subType.
		*/
		void setSubType(const std::string& subType);

		/**
		* Accessor for subType of the ReactionAttributed.
		* @return string type value of the subType.
		*/
		std::string& getSubType();

		/**
		* Const version of the subType accessor.
		* @return const string type value of subType.
		*/
		const std::string& getSubType() const;

	private:
		std::string mSubType;		/**< Subtype associated to this instance.  */
	};

	CONCRETE_FACTORY(Reaction, ReactionAttributed)
}
#pragma once

namespace MahatmaGameEngine
{
	/**
	* WordState is simply a struct to cache pointers to the current World, Sector and Entity.
	* It also includes a reference to 
	*/
	struct WorldState
	{
		WorldState();

		class World* mCurrentWorld;
		class Sector* mCurrentSector;
		class Entity* mCurrentEntity;
		class Action* mCurrentAction;
		class GameTime* mGameTime;
		class EventQueue* mEventQueue;
	};
}
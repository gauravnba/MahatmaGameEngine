#pragma once

#include <chrono>
#include "GameClock.h"

namespace MahatmaGameEngine
{
	class GameTime final
	{
	public:
		GameTime();

		const std::chrono::high_resolution_clock::time_point& currentTime() const;
		void setCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);
		
		const std::chrono::milliseconds& totalGameTime() const;
		void setTotalGameTime(const std::chrono::milliseconds& totalGameTime);

		const std::chrono::milliseconds& elapsedGameTime() const;
		void setElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime);

	private:
		std::chrono::high_resolution_clock::time_point mCurrentTime;
		std::chrono::milliseconds mTotalGameTime;
		std::chrono::milliseconds mElapsedGameTime;
	};
}

#pragma once

#include <exception>
#include <chrono>

namespace MahatmaGameEngine
{
    class GameTime;

    class GameClock
    {
    public:
        GameClock();
		GameClock(const GameClock& rhs) = delete;
		GameClock& operator=(const GameClock& rhs) = delete;

		const std::chrono::high_resolution_clock::time_point& startTime() const;
		const std::chrono::high_resolution_clock::time_point& currentTime() const;
		const std::chrono::high_resolution_clock::time_point& lastTime() const;

        void reset();
        void updateGameTime(GameTime& gameTime);

    private:
        std::chrono::high_resolution_clock::time_point mStartTime;
		std::chrono::high_resolution_clock::time_point mCurrentTime;
		std::chrono::high_resolution_clock::time_point mLastTime;
    };
}

#include "pch.h"

using namespace std::chrono;

namespace MahatmaGameEngine
{
    GameClock::GameClock() :
		mStartTime(), mCurrentTime(), mLastTime()
    {
        reset();
    }

	const high_resolution_clock::time_point& GameClock::startTime() const
    {
        return mStartTime;
    }

	const high_resolution_clock::time_point& GameClock::currentTime() const
    {
        return mCurrentTime;
    }

	const high_resolution_clock::time_point& GameClock::lastTime() const
    {
        return mLastTime;
    }

    void GameClock::reset()
    {
		mStartTime = high_resolution_clock::now();
        mCurrentTime = mStartTime;
        mLastTime = mCurrentTime;
    }

    void GameClock::updateGameTime(GameTime& gameTime)
    {
		mCurrentTime = high_resolution_clock::now();

		gameTime.setCurrentTime(mCurrentTime);
		gameTime.setTotalGameTime(duration_cast<milliseconds>(mCurrentTime - mStartTime));
		gameTime.setElapsedGameTime(duration_cast<milliseconds>(mCurrentTime - mLastTime));
        mLastTime = mCurrentTime;
    }
}
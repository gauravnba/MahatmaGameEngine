#include "pch.h"

using namespace std::chrono;

namespace MahatmaGameEngine
{
	GameTime::GameTime()
		: mCurrentTime(), mTotalGameTime(0), mElapsedGameTime(0)
	{
	}

	const high_resolution_clock::time_point& GameTime::currentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::setCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const milliseconds& GameTime::totalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::setTotalGameTime(const std::chrono::milliseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const milliseconds& GameTime::elapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::setElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}
#include "level.h"

Level::Level()
{
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
}

/** Called every frame. Updates track playing at every specified interval */
void Level::update()
{
	float frameTime = GetFrameTime();
	m_time_in_seconds += frameTime;
	m_current_interval_time += frameTime;

	if (m_current_interval_time >= INTERVAL_TIME)
	{
		m_current_interval_time -= INTERVAL_TIME;
		m_track.advance();
	}
}
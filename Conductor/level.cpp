#include "level.h"

Level::Level()
{
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
	m_track = Track();
}

Track& Level::getTrack() { return m_track; }

/** Called every frame. Updates track playing at every specified interval */
void Level::update()
{
	m_track.update(GetFrameTime());
}
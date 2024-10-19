#include "level.h"

Level::Level(const char* audio_file) : m_player(MusicPlayer(audio_file)), m_track(m_player.length())
{
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
	
}

Track& Level::getTrack() { return m_track; }

void Level::play()
{
	m_player.play();
}

/** Called every frame. Updates track playing at every specified interval */
void Level::update()
{
	m_track.update(GetFrameTime());

	if (IsKeyPressed(KEY_E)) {
		m_player.start_effect();
	}

	m_player.update();
}
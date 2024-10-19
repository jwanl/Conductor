#include "level.h"

#include <iostream>


Level::Level(const char* audio_file) : m_player(MusicPlayer(audio_file, 4.0f, 0.3f, 200.0f)), m_track(m_player.length())
{
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
	m_baton_up = false;
	m_hit_flag = false;
	m_miss_flag = false;
	m_over_flag = false;
}

Level::~Level()
{
	m_player.unload();
}

Track& Level::getTrack() { return m_track; }

void Level::play()
{
	m_player.play();
}

int Level::score() const
{
	return m_score;
}

/** Called every frame. Updates track playing at every specified interval */
void Level::update()
{
	m_player.update();
	m_track.update(GetFrameTime());

	static int num = 0;
	

	auto sub = m_track.getNextValues();
	double leftSide = m_track.getTime();

	const auto window = 0.15f;
	
	num = 0;
	for (const auto& item : sub)
	{
		const auto dt = (item.x - leftSide);
		if (dt >= -window && dt <= window) {
			num += 1;
		}
	}

	
	m_hit_flag = false;
	m_miss_flag = false;

	if (leftSide >= m_track.getLength() + 1.0f)
	{
		// set over flag and return: input is not longer registered after this
		m_over_flag = true;
		return;
	}

	if (IsKeyPressed(KEY_SPACE)) {
		if (num > 0) {
			num--;
			m_score += 100;
			m_hit_flag = true;
		}
		else {
			m_score -= 250;
			m_player.start_effect();
			m_miss_flag = true;
		}
	}

	
	m_baton_up = IsKeyDown(KEY_SPACE);


	if (!m_player.is_playing()) {
		m_over_flag = true;
	}
}
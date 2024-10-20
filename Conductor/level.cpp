#include "level.h"

#include <iostream>


Level::Level(const char* audio_file, int length) : m_player(MusicPlayer(audio_file, 4.0f, 0.3f, 200.0f)), m_track(m_player.length())
{
	m_length = length;
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
	m_baton_up = false;
	m_hit_flag = false;
	m_miss_flag = false;
	m_over_flag = false;
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
	m_time_in_seconds += GetFrameTime();

	static int num = 0;
	

	auto sub = m_track.getNextValues();
	double leftSide = m_track.getTime();

	const auto window = 0.1f;
	
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

	// fade out when 2 seconds left
	if (m_length - m_time_in_seconds <= 2)
	{
		float multiplier = std::max((float)(m_length - m_time_in_seconds), 0.0f) * 0.5f;
		m_player.set_volume(0.3f * multiplier);
	}

	if (m_time_in_seconds > m_length || !m_player.is_playing() || IsKeyPressed(KEY_P)) {
		m_over_flag = true;
	}

	
}

float Level::getPercentageDone() const {
	float perc = m_time_in_seconds / (float)m_length;
	return std::max(std::min(perc, 1.0f), 0.0f);
}
#include "level.h"

#include <iostream>


Level::Level(const char* audio_file) : m_player(MusicPlayer(audio_file, 3.0f, 0.2f, 150.0f)), m_track(m_player.length())
{
	m_time_in_seconds = 0.0;
	m_current_interval_time = 0.0f;
	m_baton_up = false;
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
		const auto dt = (item.x - m_track.m_time);
		if (dt >= -window && dt <= window) {
			num += 1;
		}
		const auto& tex = m_track.m_objects[item.i];
		//DrawTextureEx(tex, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, 180.0f, 1.0f, WHITE);
		DrawTextureRec(tex, Rectangle{ 0, 0  , (float)tex.width, -(float)tex.height }, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, GREEN);
		//DrawTexture(tex, (item.x - leftSide) * 128, item.y * 64 + 32, WHITE);
		//DrawCircle((item.x - leftSide) * 128, item.y * 64 + 32, 8, BLUE);


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
		std::cout << m_score << "\n";
	}

	
	m_baton_up = IsKeyDown(KEY_SPACE);

	
}
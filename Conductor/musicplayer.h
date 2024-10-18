#pragma once

#include "raylib.h"

#include <vector>
#include <random>


class MusicPlayer {
public:
	MusicPlayer(const char* audio_file);

	void play();
	void pause();
	void stop();

	bool is_paused() const;

	void update(float score);

private:
	//std::vector<Music> m_tracks;
	std::mt19937 m_rng;
	
	Music m_music;
	bool m_is_paused = false;
	float m_prev_score = 1.0f;
};
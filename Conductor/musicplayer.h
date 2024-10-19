#pragma once

#include "raylib.h"

#include <vector>
#include <random>


class MusicPlayer {
public:
	MusicPlayer(const char* audio_file);

	void play();

	void update();

	void start_effect();
private:
	//std::vector<Music> m_tracks;
	std::mt19937 m_rng;
	
	Music m_music;
	
	bool effect_on = false;
	float start = 0;
	float length = 0;
	float pitch = 0;
	float freq = 0;

	float music_start = 0;
};
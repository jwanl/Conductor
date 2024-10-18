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
	float strength;
	float freq, mult;
};
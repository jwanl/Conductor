#pragma once

#include "raylib.h"
#include "main.h"

#include <vector>
#include <random>




class MusicTrack {
public:
	MusicTrack(const char* audio_file);

	void play();
	void set_volume(float vol);
	void set_pan(float pan);
	void update();

	void start_effect();
//private:
	Random m_random;
	Music m_music;
	
	bool effect_on = false;
	float start = 0;
	float length = 0;
	float pitch = 1.0;
	float freq = 0;

	float music_start = 0;
};

class MusicPlayer {
public:
	MusicPlayer(const char* audio_file);

	void play();
	void update();
	void start_effect();

	float length() const;

	//private:
	MusicTrack m1, m2, m3;
};
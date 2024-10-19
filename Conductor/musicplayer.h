#pragma once

#include "raylib.h"
#include "main.h"

#include <vector>
#include <random>




class MusicTrack {
public:
	MusicTrack(const char* audio_file, float max_len, float pitch_deviation, float max_freq);

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
	
	const float max_freq;
	const float pitch_deviation;
	const float max_len;

	float music_start = 0;
};

class MusicPlayer {
public:
	MusicPlayer(const char* audio_file, float max_len, float pitch_deviation, float max_freq);

	void play();
	void update();
	void start_effect();
	inline void set_volume(float vol) { 
		m1.set_volume(vol);
		m2.set_volume(vol);
		m3.set_volume(vol);
	}

	float length() const;

	//private:
	MusicTrack m1, m2, m3;
};
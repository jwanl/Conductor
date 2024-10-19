#pragma once

#include "track.h"
#include "raylib.h"
#include "musicplayer.h"

#define INTERVAL_TIME 1.0f/8.0f

class Level
{
public:
	Level(const char* audio_file);
	void update();
	Track& getTrack();

	void play();
private:
	MusicPlayer m_player;
	Track m_track;
	double m_time_in_seconds;
	float m_current_interval_time;
};
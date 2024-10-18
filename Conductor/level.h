#pragma once

#include "track.h"
#include "raylib.h"

#define INTERVAL_TIME 1.0f/8.0f

class Level
{
public:
	Level();
	void update();
	Track& getTrack();
private:
	Track m_track;
	double m_time_in_seconds;
	float m_current_interval_time;
};
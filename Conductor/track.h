#pragma once

#include <vector>
#include <algorithm>
#include "track_data.h"
#include "raylib.h"
#include "main.h"

struct TrackObject {
	float x, y;
	int i;
};

class Track 
{
public:
	Track(float track_time);
	void update(float frameTime);
	bool isOver();
	const std::vector<TrackObject> getNextValues() const;
	float getWindow() const;
	double getTime() const;
//private:
	std::size_t m_step = 0;
	double m_time = 0.0;
	std::vector<TrackObject> m_track_data;
	float m_window = 8.0f;
	Random m_random;

	std::vector<Texture2D> m_objects;
};
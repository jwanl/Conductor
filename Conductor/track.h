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
	float getLength() const { return m_track_length; }

	std::vector<Texture2D> m_objects;
private:
	std::size_t m_step;
	double m_time;
	std::vector<TrackObject> m_track_data;
	float m_window;
	Random m_random;
	float m_track_length;
};
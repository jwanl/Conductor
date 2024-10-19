#pragma once

#include <vector>
#include <algorithm>
#include "track_data.h"
#include "raylib.h"
#include "main.h"

class Track 
{
public:
	Track(float track_time);
	void update(float frameTime);
	bool isOver();
	const std::vector<Vector2> getNextValues() const;
	float getWindow() const;
	double getTime() const;
private:
	std::size_t m_step = 0;
	double m_time = 0.0;
	std::vector<Vector2> m_track_data;
	float m_window = 8.0f;
	Random m_random;
};
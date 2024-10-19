#include "track.h"

Track::Track() 
{
	m_window = 4.0f;
	m_step = 0;
	m_time = 0.0;
	m_track_data = { track1_data };
	std::sort(m_track_data.begin(), m_track_data.end(), [](Vector2 a, Vector2 b) { return a.x < b.x; });
}

void Track::update(float frameTime)
{
	m_time += frameTime;
	if (!isOver())
	{
		// check if we can update step so it is faster to read data as we already know where to start
		if (m_track_data.at(m_step).x < m_time)
		{
			m_step++;
		}
	}
}

float Track::getWindow() const { return m_window; }

double Track::getTime() const { return m_time; }

bool Track::isOver()
{
	return m_step >= m_track_data.size();
}

const std::vector<Vector2> Track::getNextValues() const
{
	auto start = m_step < 3 ? m_track_data.begin() + m_step : m_track_data.begin() + m_step - 3;
	auto end = std::find_if(start, m_track_data.end(), [&](Vector2 a) { return a.x >= m_time + m_window; });
	
	std::vector<Vector2> sub(start, end);
	return sub;
}
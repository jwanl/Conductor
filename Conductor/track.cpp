#include "track.h"

Track::Track() 
{
	m_time_iterator = 0;
	m_track_data = { track1_data };
}

void Track::advance()
{
	m_time_iterator++;
}

bool Track::isOver()
{
	return m_time_iterator >= m_track_data.size();
}

std::vector<bool>::const_iterator Track::getCurrentValue() const
{
	return (m_track_data.begin() + m_time_iterator);
}

std::vector<bool>::const_iterator Track::getEnd() const
{
	return m_track_data.end();
}
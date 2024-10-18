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
<<<<<<< HEAD
	m_time_iterator >= m_track_data.size();
	throw "";
=======
	return m_time_iterator >= m_track_data.size();
}

std::vector<bool>::const_iterator Track::getCurrentValue() const
{
	return (m_track_data.begin() + m_time_iterator);
}

std::vector<bool>::const_iterator Track::getEnd() const
{
	return m_track_data.end();
>>>>>>> 6f81d59855097c64a559addb4f2de2a9f63b4ef2
}
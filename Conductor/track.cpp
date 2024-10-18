#include "track.h"

void Track::advance()
{
	m_time_iterator++;
}

bool Track::isOver()
{
	m_time_iterator >= m_track_data.size();
}
#pragma once

#include <vector>

class Track 
{
public:
	void advance();
	bool isOver();
private:
	std::size_t m_time_iterator = 0;
	std::vector<bool> m_track_data;
};
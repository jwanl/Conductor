#pragma once

#include <vector>
#include "track_data.h"

class Track 
{
public:
	Track();
	void advance();
	bool isOver();
	std::vector<bool>::const_iterator getCurrentValue() const;
	std::vector<bool>::const_iterator getEnd() const;
private:
	std::size_t m_time_iterator = 0;
	std::vector<bool> m_track_data;
};
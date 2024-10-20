#pragma once

#include "track.h"
#include "raylib.h"
#include "musicplayer.h"


class Level
{
public:
	Level(const char* audio_file, int length);
	~Level();
	void update();
	Track& getTrack();
	bool isBatonUp() const { return m_baton_up; }

	void play();
	int score() const;
	bool getHit() const { return m_hit_flag; }
	bool getMiss() const { return m_miss_flag; }
	bool isOver() const { return m_over_flag; }
	int getLength() const { return m_length; }
	float getPercentageDone() const;
private:

	int m_score = 0;
	MusicPlayer m_player;
	Track m_track;
	double m_time_in_seconds;
	float m_current_interval_time;
	bool m_baton_up;
	bool m_hit_flag;
	bool m_miss_flag;
	bool m_over_flag;
	int m_length;

};
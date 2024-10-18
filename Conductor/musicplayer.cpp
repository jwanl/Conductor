#include "musicplayer.h"

#include <iostream>
MusicPlayer::MusicPlayer(const char* audio_file) {
	m_rng = std::mt19937(std::random_device()());
	m_music = LoadMusicStream(audio_file);
	m_music.looping = false;
}

void MusicPlayer::play() {
	PlayMusicStream(m_music);
	
	m_is_paused = false;
}

void MusicPlayer::pause() {
	if (m_is_paused) {
		ResumeMusicStream(m_music);
		m_is_paused = false;
	}
	else {
		PauseMusicStream(m_music);
		m_is_paused = true;
	}
}

void MusicPlayer::stop() {
	StopMusicStream(m_music);
	m_is_paused = true;
}

bool MusicPlayer::is_paused() const {
	return m_is_paused;
}


void MusicPlayer::update(float score) {
	const auto s = std::abs(1.0f - score) * 0.02f;
	auto dist = std::uniform_real_distribution<float>(-s, s);



	//const auto f = 10.0f;

	//const auto d = std::sin(GetTime() * f) * (1.0f - score);


	if (!m_is_paused) {
		auto p = m_prev_score + dist(m_rng);
		if (p < 0.1f) p = 0.1f;
		else if (p > 1.9f) p = 1.9f;

		const auto d = 1.0f - p;

		p += 0.01f * d;


		m_prev_score = p;



		SetMusicPitch(m_music, p);
		//std::cout << ds << "\n";
		UpdateMusicStream(m_music);
	}
}
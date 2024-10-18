#include "musicplayer.h"

#include <iostream>
MusicPlayer::MusicPlayer(const char* audio_file) {
	m_rng = std::mt19937(std::random_device()());
	m_music = LoadMusicStream(audio_file);
	m_music.looping = false;

	strength = 0;
	freq = 0;
	mult = 0;
}

void MusicPlayer::play() {
	PlayMusicStream(m_music);

}

void MusicPlayer::start_effect() {
	auto dist = std::uniform_real_distribution<float>(0.0f, 1.0f);

	strength = 1.0f;
	mult = 1.0f - dist(m_rng) * 0.1f;
	freq = dist(m_rng) * 200;
}

void MusicPlayer::update() {
	if (strength > 0.1f) {
		const auto dp = std::sin(GetTime() * freq) * strength * 0.5f;
		strength *= mult;

		SetMusicPitch(m_music, 1.0f + dp);
		std::cout << strength << "\n";
	}

	UpdateMusicStream(m_music);
}
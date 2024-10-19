#include "musicplayer.h"

#include <iostream>
MusicPlayer::MusicPlayer(const char* audio_file) {
	m_rng = std::mt19937(std::random_device()());
	m_music = LoadMusicStream(audio_file);
	m_music.looping = false;


}

void MusicPlayer::play() {
	PlayMusicStream(m_music);
	music_start = GetTime();
}

void MusicPlayer::start_effect() {
	auto dist = std::uniform_real_distribution<float>(0.0f, 1.0f);

	const auto max_length = 3.0f;
	const auto max_freq = 50.0f;

	const auto max_pitch = 1.2f;
	const auto min_pitch = 0.8f;

	effect_on = true;
	start = GetTime();
	length = dist(m_rng) * max_length + 0.01f;
	freq = dist(m_rng) * max_freq;

	pitch = dist(m_rng) * (max_pitch - min_pitch) + min_pitch;
}

void MusicPlayer::update() {
	if (effect_on) {
		const auto t = GetTime() - start;
		if (t > length) {
			effect_on = false;
		}
		else {
			const auto k = t / length;
			const auto p = k * pitch + (1.0f - k)* std::sin(t * freq) * 0.1f;
			SetMusicPitch(m_music, p);
		}
	}
	else {
		const auto t = GetTime() - music_start;
		const auto error = t - GetMusicTimePlayed(m_music);

		const auto max_pitch = 2.0f;
		const auto min_pitch = 0.5f;

		pitch = 1.0f + error * 0.3f;

		/*if (error > 0.1f) {
			pitch = 1.0f + e
		}
		else if (error < -0.1f) {
			pitch = 1.0f - std::pow(0.1f, t1 * 0.1f);
		}*/
		

		pitch = pitch > max_pitch ? max_pitch : pitch < min_pitch? min_pitch : pitch;

		SetMusicPitch(m_music, pitch);

		
	}
	std::cout << pitch << "\n";

	UpdateMusicStream(m_music);
}
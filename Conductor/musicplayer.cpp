#include "musicplayer.h"

#include <iostream>



MusicTrack::MusicTrack(const char* audio_file) {
	m_random = Random();
	m_music = LoadMusicStream(audio_file);
	m_music.looping = false;


}

void MusicTrack::play() {
	PlayMusicStream(m_music);
	music_start = GetTime();
}

void MusicTrack::set_volume(float vol)
{
	vol = vol > 1.0f ? 1.0f : vol < 0.0f ? 0.0f : vol;
	SetMusicVolume(m_music, vol);
}

void MusicTrack::set_pan(float pan)
{
	pan = pan > 1.0f ? 1.0f : pan < 0.0f ? 0.0f : pan;
	SetMusicPan(m_music, pan);
}

void MusicTrack::start_effect() {

	const auto max_length = 2.0f;
	const auto max_freq = 150.0f;

	const auto max_pitch = 1.2f;
	const auto min_pitch = 0.5f;

	effect_on = true;
	start = GetTime();
	length = m_random.get() * max_length + 0.01f;
	freq = m_random.get() * max_freq;

	pitch = m_random.get() * (max_pitch - min_pitch) + min_pitch;
}

void MusicTrack::update() {
	if (effect_on) {
		const auto t = GetTime() - start;
		if (t > length) {
			effect_on = false;
		}
		else {
			const auto k = t / length;
			const auto p = k * pitch + (1.0f - k) * std::sin(t * freq) * 0.1f;
			SetMusicPitch(m_music, p);
		}
	}
	else {
		const auto t = GetTime() - music_start;
		const auto error = t - GetMusicTimePlayed(m_music);


		const auto max_pitch = 2.0f;
		const auto min_pitch = 0.5f;

		pitch = 1.0f + error * 0.5f;

		/*if (error > 0.1f) {
			pitch = 1.0f + e
		}
		else if (error < -0.1f) {
			pitch = 1.0f - std::pow(0.1f, t1 * 0.1f);
		}*/
		

		pitch = pitch > max_pitch ? max_pitch : pitch < min_pitch? min_pitch : pitch;

		SetMusicPitch(m_music, pitch);

		
	}

	UpdateMusicStream(m_music);
}

MusicPlayer::MusicPlayer(const char* audio_file) : m1(MusicTrack(audio_file)), m2(MusicTrack(audio_file)), m3(MusicTrack(audio_file))
{
	m1.set_volume(0.6f);
	m2.set_volume(0.5f);
	m3.set_volume(0.5f);
}

void MusicPlayer::play()
{
	m1.play();
	m2.play();
	m3.play();
}

void MusicPlayer::update()
{
	m1.update();
	m2.update();
	m3.update();
}

void MusicPlayer::start_effect()
{
	m2.start_effect();
	m3.start_effect();
}

float MusicPlayer::length() const
{
	return GetMusicTimeLength(m1.m_music);
}

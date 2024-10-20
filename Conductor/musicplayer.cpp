#include "musicplayer.h"

#include <iostream>



MusicTrack::MusicTrack(const char* audio_file, float max_len, float pitch_deviation, float max_freq) :
	max_len(max_len), pitch_deviation(pitch_deviation), max_freq(max_freq)
{
	m_random = Random();
	m_music = LoadMusicStream(audio_file);
	m_music.looping = false;


}

void MusicTrack::play() {
	PlayMusicStream(m_music);
	music_start = GetTime();
}

void MusicTrack::stop()
{
	StopMusicStream(m_music);
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
	if (!effect_on) {
		const auto max_pitch = 1.0f + pitch_deviation;
		const auto min_pitch = 1.0f - pitch_deviation;

		effect_on = true;
		start = GetTime();
		length = m_random.get() * max_len + 0.01f;
		freq = m_random.get() * max_freq;

		pitch = m_random.get() * (max_pitch - min_pitch) + min_pitch;
	}
	

	
}

void MusicTrack::update() {
	time_since_update += GetFrameTime();
	
	if (time_since_update < 0.2f) {
		UpdateMusicStream(m_music);
		return;
	}

	time_since_update = 0;
	

	if (effect_on) {
		const auto t = GetTime() - start;
		if (t > length) {
			effect_on = false;
		}
		else {
			const auto k = t / length;
			auto p = k * pitch + (1.0f - k) * std::sin(t * freq) * 0.1f;
			if (p < 0.1f) {
				p = 0.1f;
			}

			SetMusicPitch(m_music, p);
		}
	}
	else {
		const auto t = GetTime() - music_start;
		const auto error = t - GetMusicTimePlayed(m_music);


		const auto max_pitch = 1.5f;
		const auto min_pitch = 0.5f;

		pitch = 1.0f + error * 0.5f;

		if (std::abs(error) > 0.001f) {
			pitch = pitch > max_pitch ? max_pitch : pitch < min_pitch ? min_pitch : pitch;

			SetMusicPitch(m_music, pitch);
		}
		

		

		/*if (error > 0.1f) {
			pitch = 1.0f + e
		}
		else if (error < -0.1f) {
			pitch = 1.0f - std::pow(0.1f, t1 * 0.1f);
		}*/
		

		

		
	}
	
	UpdateMusicStream(m_music);

	
}

MusicPlayer::MusicPlayer(const char* audio_file, float max_len, float pitch_deviation, float max_freq) :
	m1(MusicTrack(audio_file, max_len, pitch_deviation, max_freq)),
	m3(MusicTrack(audio_file, max_len, pitch_deviation, max_freq))
{
	m1.set_volume(0.3f);
	m3.set_volume(0.3f);
}

MusicPlayer::~MusicPlayer()
{
	m1.stop();
	m3.stop();
	//m1.unload();
	//m3.unload();
}

void MusicPlayer::play()
{
	m1.play();
	m3.play();
}

void MusicPlayer::stop()
{
	m1.stop();
	m3.stop();
}

void MusicPlayer::update()
{
	m1.update();
	m3.update();
}

void MusicPlayer::start_effect()
{
	m3.start_effect();
}

float MusicPlayer::length() const
{
	return GetMusicTimeLength(m1.m_music);
}

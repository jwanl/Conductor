#include "track.h"


Track::Track(float track_time) 
{
	m_track_length = track_time;
	m_window = 5.0f;
	m_step = 0;
	m_time = 0.0;
	m_random = Random();
	//m_track_data = { track1_data };
	const auto N = (int)(track_time * 20.0f);

	

	m_objects.push_back(LoadTexture(RES("avain.png")));
	m_objects.push_back(LoadTexture(RES("break.png")));
	m_objects.push_back(LoadTexture(RES("csharp.png")));
	m_objects.push_back(LoadTexture(RES("double.png")));
	m_objects.push_back(LoadTexture(RES("ff.png")));
	m_objects.push_back(LoadTexture(RES("flat.png")));
	m_objects.push_back(LoadTexture(RES("nuotti.png")));
	m_objects.push_back(LoadTexture(RES("nuotti2.png")));
	m_objects.push_back(LoadTexture(RES("sharp.png")));
	m_objects.push_back(LoadTexture(RES("cpp.png")));
	m_objects.push_back(LoadTexture(RES("dx.png")));
	m_objects.push_back(LoadTexture(RES("dolla.png")));
	m_objects.push_back(LoadTexture(RES("nabla.png")));

	

	for (int i = 0; i < N; i++) {
		TrackObject obj;
		obj.x = m_random.get() * 5 * track_time + 5;
		obj.y = m_random.get() * 0.7f - 0.4f;
		obj.i = (int)(m_random.get() * (m_objects.size() - 1));
		m_track_data.push_back(obj);
	}
	std::sort(m_track_data.begin(), m_track_data.end(), [](TrackObject& a, TrackObject& b) { return a.x < b.x; });
}

void Track::update(float frameTime)
{
	m_time += frameTime;
	if (!isOver())
	{
		// check if we can update step so it is faster to read data as we already know where to start
		if (m_track_data.at(m_step).x < m_time)
		{
			m_step++;
		}
	}
}

float Track::getWindow() const { return m_window; }

double Track::getTime() const { return m_time; }

bool Track::isOver()
{
	return m_step >= m_track_data.size();
}

const std::vector<TrackObject> Track::getNextValues() const
{
	auto start = m_step < 3 ? m_track_data.begin() + m_step : m_track_data.begin() + m_step - 3;
	auto end = std::find_if(start, m_track_data.end(), [&](const TrackObject& a) { return a.x >= m_time + m_window; });


	
	std::vector<TrackObject> sub(start, end);
	return sub;
}
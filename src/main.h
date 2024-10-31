#pragma once

#include <random>

#if defined(NDEBUG) || defined(PLATFORM_WEB)

#define RES(path) "resources/"  path
#else

#define RES(path) "../../resources/"  path
#endif



class Random {
public:
	inline Random() {
		m_rng = std::mt19937(std::random_device()());
		m_dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
	}

	inline float get() {
		return m_dist(m_rng);
	}

private:
	std::mt19937 m_rng;
	std::uniform_real_distribution<float> m_dist;
};

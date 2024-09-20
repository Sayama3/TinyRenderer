//
// Created by Sayama on 13/09/2024.
//

#include "TinyRenderer/Core/Random.hpp"

namespace tr
{

	Random::Random(uint64_t seed) : m_left(seed >> 32), m_right(seed)
	{
	}

	Random::Random(uint32_t w, uint32_t z) : m_right(w), m_left(z)
	{
	}

	uint64_t Random::Value() {
		m_left = 36969 * (m_left & 65535) + (m_left >> 16);
		m_right = 18000 * (m_right & 65535) + (m_right >> 16);
		return Seed();
	}

	uint64_t Random::Seed() {
		return ((uint64_t)m_left << 32) | m_right;
	}

	double Random::DValue() {
		return (double)Value() /(double)UINT64_MAX;
	}

	float Random::FValue() {
		return (float)Value() /(float)UINT64_MAX;
	}

	float Random::FValue(float min, float max) {
		return FValue() * (max-min) + min;
	}
}
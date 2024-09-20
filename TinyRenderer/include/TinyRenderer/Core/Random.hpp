//
// Created by Sayama on 13/09/2024.
//

#pragma once

#include <cstdint>

namespace tr
{
	class Random
	{
	public:
		Random() = default;
		Random(uint64_t seed);
		Random(uint32_t w, uint32_t z);

		uint64_t Value();
		double DValue();
		float FValue();
		float FValue(float min, float max);
		uint64_t Seed();
	public:
		uint32_t m_left;
		uint32_t m_right;
	};
}
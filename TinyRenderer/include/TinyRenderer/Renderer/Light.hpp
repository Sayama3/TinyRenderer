//
// Created by Sayama on 12/09/2024.
//

#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "TinyRenderer/Core/Math.hpp"

namespace tr
{
	enum class LightType : int
	{
		Directional,
		Point,
		Spot
	};

	inline std::vector<std::string> GetLightTypeName() { return {"Directional", "Point", "Spot"};}

	struct Light
	{
		inline Light() = default;
		inline ~Light() = default;
		inline Light(Vec4 color, Vec3 position, Vec3 direction, float range, float intensity, float cutoff, LightType type) : Color(color), Position(Vec4(position, 1)), Direction(Vec4(direction, 0)), Range(range), Intensity(intensity), Cutoff(cutoff), Type((int)type) {}

		Vec4 Color;
		Vec4 Position;
		Vec4 Direction;
		float Range;
		float Intensity;
		float Cutoff;
		int Type;
	};
}
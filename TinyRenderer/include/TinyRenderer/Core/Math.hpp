//
// Created by Sayama on 09/09/2024.
//

#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <cstdint>

using Mat4 = glm::mat4;
using Mat3 = glm::mat3;

using Quat = glm::quat;

using Vec4 = glm::vec4;
using Vec3 = glm::vec3;
using Vec2 = glm::vec2;

namespace tr::Math
{
	inline void TRS(Mat4& trs, const Vec3& position, const Quat& rotation)
	{
		trs = glm::translate(trs, position); // Translation Matrix
		trs = trs * glm::toMat4(rotation); // Rotation Matrix
	}

	inline void TRS(Mat4& trs, const Vec3& position, const Quat& rotation, const Vec3& scale)
	{
		trs = glm::translate(trs, position); // Translation Matrix
		trs = trs * glm::toMat4(rotation); // Rotation Matrix
		if(scale.x != 1 && scale.y != 1 && scale.z != 1)
			trs = glm::scale(trs, scale); // Scale Matrix
	}

	inline Mat4 TRS(const Vec3& position, const Quat& rotation)
	{
		Mat4 trs = glm::identity<glm::mat4>();
		TRS(trs, position, rotation);
		return trs;
	}

	inline Mat4 TRS(const Vec3& position, const Quat& rotation, const Vec3& scale)
	{
		Mat4 trs = glm::identity<glm::mat4>();
		TRS(trs, position, rotation, scale);
		return trs;
	}

} // tr

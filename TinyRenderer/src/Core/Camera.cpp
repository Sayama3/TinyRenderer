//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Camera.hpp"

namespace tr {
	Camera::Camera(uint32_t width, uint32_t height, float radianFov, float nearClip, float farClip) : AspectRatio(float(width)/float(height)), RadFov(radianFov), Near(nearClip), Far(farClip)
	{
	}

	Camera::Camera(float aspectRatio, float radianFov, float nearClip, float farClip) : AspectRatio(aspectRatio), RadFov(radianFov), Near(nearClip), Far(farClip)
	{
	}

	glm::mat4 Camera::GetProjectionMatrix() const {
		return glm::perspective(RadFov, AspectRatio, Near, Far);
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::inverse(Math::TRS(Position, Rotation));
	}

	glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return GetProjectionMatrix() * GetViewMatrix();
	}
} // tr
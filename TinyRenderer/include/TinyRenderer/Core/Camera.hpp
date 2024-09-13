//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "TinyRenderer/Core/Math.hpp"

namespace tr {

	class IProjection {
	public:
		virtual ~IProjection() = default;
		[[nodiscard]] virtual Mat4 GetProjectionMatrix() const = 0;
	};

	class IView {
	public:
		virtual ~IView() = default;
		[[nodiscard]] virtual Mat4 GetViewMatrix() const = 0;
	};

	class Camera : public IProjection, public IView {
	public:
		Camera() = default;
		explicit Camera(uint32_t width, uint32_t height, float radianFov = glm::radians(60.0f), float nearClip = 0.001f, float farClip = 1000.0f);
		explicit Camera(float aspectRatio, float radianFov = glm::radians(60.0f), float nearClip = 0.001f, float farClip = 1000.0f);
		~Camera() = default;

	public:
		[[nodiscard]] virtual Mat4 GetProjectionMatrix() const override;
		[[nodiscard]] virtual Mat4 GetViewMatrix() const override;
		[[nodiscard]] Mat4 GetViewProjectionMatrix() const;

		[[nodiscard]] Vec3 GetUp() const {return Rotation * Vec3{0,1,0};}
		[[nodiscard]] Vec3 GetForward() const {return Rotation * Vec3{0,0,1};}
	public:
		Vec3 Position{};
		Quat Rotation{glm::identity<Quat>()};

		/// FOV in radians
		float RadFov = glm::radians(60.0f);
		float AspectRatio = 16.0f/9.0f;
		float Near = 0.001f;
		float Far = 1000.0f;
	};

} // tr

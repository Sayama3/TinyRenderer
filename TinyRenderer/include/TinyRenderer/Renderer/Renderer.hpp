//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "TinyRenderer/Renderer/Shader.hpp"
#include "TinyRenderer/Renderer/Mesh.hpp"
#include "TinyRenderer/Renderer/Light.hpp"
#include "TinyRenderer/Renderer/UniformBuffer.hpp"

#include "TinyRenderer/Core/Camera.hpp"

#include "TinyRenderer/Core/Math.hpp"
#include <map>

namespace tr {

	static inline constexpr uint32_t MAX_LIGHT_COUNT = 32u;

	struct RendererData
	{
		// TODO: Add Normal Matrix
		// TODO: Add MVP Matrix
		// Both Previous todo are to reduce the load on the GPU side.
		//  But it might need a bit of checking and more data to know if it's worth.

		struct CameraData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec4 CameraPosition;
			glm::vec4 CameraDirection;
		};

		struct ModelData
		{
			inline ModelData() = default;
			inline ~ModelData() = default;
			ModelData(const glm::mat4& transformMatrix, const glm::mat4& normalMatrix, int entityId = -1);
			ModelData(const glm::mat4& transformMatrix, int entityId = -1);

			void SetMatrix(const glm::mat4& transformMatrix, const glm::mat4& normalMatrix);
			void SetMatrix(const glm::mat4& transformMatrix);

			glm::mat4 TransformMatrix;
			glm::mat4 NormalMatrix;
			int EntityId;
		};

//		struct LightData
//		{
//			Light lights[MAX_LIGHT_COUNT];
//			int lightCount;
//		};

		CameraData CameraBuffer;
		ModelData ModelBuffer;
//		LightData LightBuffer;

		std::shared_ptr<UniformBuffer> CameraUniformBuffer;
		std::shared_ptr<UniformBuffer> ModelUniformBuffer;
//		std::shared_ptr<UniformBuffer> LightUniformBuffer;

		std::multimap<float, std::tuple<const std::shared_ptr<Mesh>, glm::mat4, int>> AlphaMeshes;
	};

	class Renderer {
	public:
		static void Initialize();
		static void Terminate();
		static void Clear();

		static void SetCamera(const Camera& camera);
		static void SetShader(std::shared_ptr<Shader> shader);
		static void DrawMesh(std::shared_ptr<Mesh> mesh, const Mat4& modelMatrix);
	private:
		static inline std::unique_ptr<Camera> s_Camera{nullptr};
		static inline std::unique_ptr<RendererData> s_RenderData{nullptr};
		static inline std::shared_ptr<Shader> s_Shader{nullptr};
	};

} // tr

//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "Buffer.hpp"
#include "VertexArray.hpp"

#include <glm/glm.hpp>

namespace tr {
	struct Vertex {
		Vertex() = default;
		Vertex(const Vertex&) = default;
		Vertex& operator=(const Vertex&) = default;
		~Vertex() = default;
		Vertex(glm::vec3 pos, glm::vec3 normal = {0,1,0}, glm::vec4 color = {1,1,1,1}, glm::vec2 uv={0,0}) : pos(pos), normal(normal), color(color), uv(uv) {}

		friend bool operator!=(const Vertex& lft, const Vertex& rht) {
			return !(lft == rht);
		}

		friend bool operator==(const Vertex& lft, const Vertex& rht) {
			return std::memcmp(&lft, &rht, sizeof(Vertex)) == 0;
		}

		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec4 color;
	};


	static inline BufferLayout GetVertexBufferLayout() {
		return {
			{BufferDataType::FLOAT3, "Position"},
			{BufferDataType::FLOAT3, "Normal"},
			{BufferDataType::FLOAT2, "UV"},
			{BufferDataType::FLOAT4, "Color"},
		};
	}

	class Mesh {
	public:
		[[nodiscard]] static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertex);
		[[nodiscard]] static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertex, const std::vector<uint32_t>& indices);
	public:
		Mesh(const std::vector<Vertex>& vertex);
		Mesh(const std::vector<Vertex>& vertex, const std::vector<uint32_t>& indices);
		~Mesh();
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
	public:
		[[nodiscard]] std::shared_ptr<VertexArray> GetVertexArray() const;
	private:
		void CreateMesh(const std::vector<Vertex>& vertex, const std::vector<uint32_t>& indices);
	private:
		std::shared_ptr<VertexArray> m_VertexArray = nullptr;
	};

	class Primitives {
	public:
		static std::shared_ptr<Mesh> CreateCube();
		static std::shared_ptr<Mesh> CreateCubemapMesh();
	};

} // tr

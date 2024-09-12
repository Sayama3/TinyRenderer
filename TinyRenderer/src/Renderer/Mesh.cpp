//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Renderer/Mesh.hpp"

namespace tr {

	std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex> &vertex) {
		return std::make_shared<Mesh>(vertex);
	}

	std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex> &vertex, const std::vector<uint32_t> &indices) {
		return std::make_shared<Mesh>(vertex, indices);
	}

	Mesh::Mesh(const std::vector<Vertex> &vertex) {

		std::vector<uint32_t> indices(vertex.size());
		for (int i = 0; i < vertex.size(); ++i) indices[i] = i;
		CreateMesh(vertex, indices);
	}

	Mesh::Mesh(const std::vector<Vertex> &vertex, const std::vector<uint32_t> &indices) {
		CreateMesh(vertex, indices);
	}


	std::shared_ptr<VertexArray> Mesh::GetVertexArray() const {
		return m_VertexArray;
	}

	void Mesh::CreateMesh(const std::vector<Vertex> &vertex, const std::vector<uint32_t> &indices)
	{
		m_VertexArray = std::make_shared<VertexArray>();

		std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(Buffer{const_cast<uint32_t*>(indices.data()), indices.size()});
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(Buffer{const_cast<Vertex*>(vertex.data()), vertex.size()});
		vertexBuffer->SetLayout(GetVertexBufferLayout());
		m_VertexArray->AddVertexBuffer(vertexBuffer);
	}

	Mesh::~Mesh() = default;

	std::shared_ptr<Mesh> Primitives::CreateCube() {
		std::vector<Vertex> m_CubeVertices = {
				{{-1.0f, +1.0f, +1.0f}},
				{{-1.0f, -1.0f, +1.0f}},
				{{+1.0f, +1.0f, +1.0f}},
				{{+1.0f, -1.0f, +1.0f}},
				{{-1.0f, +1.0f, -1.0f}},
				{{-1.0f, -1.0f, -1.0f}},
				{{+1.0f, +1.0f, -1.0f}},
				{{+1.0f, -1.0f, -1.0f}},
		};

		std::vector<uint32_t> m_CubeIndices = {
				0, 2, 3, 0, 3, 1,
				2, 6, 7, 2, 7, 3,
				6, 4, 5, 6, 5, 7,
				4, 0, 1, 4, 1, 5,
				0, 4, 6, 0, 6, 2,
				1, 5, 7, 1, 7, 3,
		};

		return Mesh::Create(m_CubeVertices, m_CubeIndices);
	}
} // tr
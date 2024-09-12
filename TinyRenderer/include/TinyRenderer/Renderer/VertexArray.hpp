//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include <cstdint>
#include "Buffer.hpp"
#include "TinyRenderer/Core/Buffer.hpp"
#include <cstdint>
#include <optional>

namespace tr {

	class VertexArray
	{
	public:
		[[nodiscard]] static std::shared_ptr<VertexArray> Create();
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray operator=(const VertexArray&) = delete;
	public:
		void Bind();
		void Unbind();

		std::optional<uint32_t> AddVertexBuffer(std::shared_ptr<VertexBuffer> vb);
		bool SetVertexBuffer(uint32_t index, std::shared_ptr<VertexBuffer> vb);
		void RemoveVertexBuffer(uint32_t index);

		void SetIndexBuffer(std::shared_ptr<IndexBuffer> vb);
		[[nodiscard]] uint32_t GetRenderID() const;

		uint32_t GetDrawCount() const;
	private:
		uint32_t m_RenderID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer {};
		std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;
	};

} // tr

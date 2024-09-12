//
// Created by Sayama on 12/09/2024.
//

#include "TinyRenderer/Renderer/UniformBuffer.hpp"
#include <glad/glad.h>

namespace tr {
	std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding) {
		return std::make_shared<UniformBuffer>(size, binding);
	}

	UniformBuffer::UniformBuffer(uint32_t size, uint32_t binding) {
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	UniformBuffer::~UniformBuffer() {
		glDeleteBuffers(1, &m_RendererID);

	}

	void UniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) {
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

	void UniformBuffer::SetData(tr::Buffer buffer) {
		SetData(buffer.data, buffer.size, 0);
	}
} // tr
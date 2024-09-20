//
// Created by Sayama on 13/09/2024.
//

#include "TinyRenderer/Renderer/SSBO.hpp"

#include <glad/glad.h>

namespace tr {

	std::shared_ptr<SSBO> SSBO::Create()
	{
		return std::make_shared<SSBO>();
	}
	std::shared_ptr<SSBO> SSBO::Create(Buffer buffer, SSBOUsage usage)
	{
		return std::make_shared<SSBO>(buffer, usage);
	}
	std::shared_ptr<SSBO> SSBO::Create(uint64_t size, SSBOUsage usage)
	{
		return std::make_shared<SSBO>(size, usage);
	}

	GLenum getUsage(SSBOUsage usage)
	{
		switch (usage) {
			case SSBOUsage::StreamDraw: 	return GL_STREAM_DRAW;
			case SSBOUsage::StreamRead: 	return GL_STREAM_READ;
			case SSBOUsage::StreamCopy: 	return GL_STREAM_COPY;
			case SSBOUsage::StaticDraw: 	return GL_STATIC_DRAW;
			case SSBOUsage::StaticRead: 	return GL_STATIC_READ;
			case SSBOUsage::StaticCopy: 	return GL_STATIC_COPY;
			case SSBOUsage::DynamicDraw: 	return GL_DYNAMIC_DRAW;
			case SSBOUsage::DynamicRead: 	return GL_DYNAMIC_READ;
			case SSBOUsage::DynamicCopy: 	return GL_DYNAMIC_COPY;
		}

		return 0;
	}

	SSBO::SSBO()
	{
		glCreateBuffers(1, &m_RendererID);
	}

	SSBO::SSBO(Buffer buffer,SSBOUsage usage) {
		glCreateBuffers(1, &m_RendererID);
		Allocate(buffer, usage);
	}

	SSBO::SSBO(uint64_t size, SSBOUsage usage) {
		glCreateBuffers(1, &m_RendererID);
		Allocate(size, usage);
	}

	SSBO::~SSBO() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void SSBO::Bind(uint32_t index) {
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_RendererID);
	}

	uint32_t SSBO::GetRendererID() const {
		return m_RendererID;
	}

	void SSBO::Allocate(Buffer buffer, SSBOUsage usage)
	{
		glNamedBufferData(m_RendererID, buffer.size, buffer.data, getUsage(usage));
	}

	void SSBO::Allocate(uint64_t size, SSBOUsage usage)
	{
		glNamedBufferData(m_RendererID, size, nullptr, getUsage(usage));
	}

	void SSBO::SetData(Buffer buffer, int64_t offset) {
		// Only in debug
		int64_t bufferSize{0};
		glGetNamedBufferParameteri64v(m_RendererID, GL_BUFFER_SIZE, &bufferSize);
		TR_ASSERT(buffer.size + offset <= bufferSize, "There is not enough allocated data in the SSBO.");

		// Anytime
		glNamedBufferSubData(m_RendererID, offset, buffer.size, buffer.data);
	}


} // tr
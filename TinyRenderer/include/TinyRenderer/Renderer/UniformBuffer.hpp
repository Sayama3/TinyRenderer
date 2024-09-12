//
// Created by Sayama on 12/09/2024.
//

#pragma once

#include "TinyRenderer/Core/Buffer.hpp"

#include <cstdint>

namespace tr {

	class UniformBuffer
	{
	public:
		UniformBuffer(uint32_t size, uint32_t binding);
		~UniformBuffer();
	public:
		static std::shared_ptr<UniformBuffer> Create(uint32_t size, uint32_t binding);

		template<typename T>
		static std::shared_ptr<UniformBuffer> Create(uint32_t binding) {return Create(sizeof(T), binding);}
	public:

		void SetData(const void* data, uint32_t size, uint32_t offset = 0);
		void SetData(tr::Buffer buffer);

		template<typename T>
		void SetData(const T& data)
		{
			SetData(&data, sizeof(T), 0);
		}
	private:
		uint32_t m_RendererID = 0;
	};

} // tr

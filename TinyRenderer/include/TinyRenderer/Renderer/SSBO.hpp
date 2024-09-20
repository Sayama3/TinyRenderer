//
// Created by Sayama on 13/09/2024.
//

#pragma once

#include "TinyRenderer/Core/Buffer.hpp"
#include <cstdint>
#include <vector>
#include <optional>

namespace tr {
	/**
	 * The frequency of access may be one of these:
	 * STREAM 	- The data store contents will be modified once and used at most a few times.
	 * STATIC 	- The data store contents will be modified once and used many times.
	 * DYNAMIC	- The data store contents will be modified repeatedly and used many times.
	 *
	 * The nature of access may be one of these:
	 * DRAW 	- The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
	 * READ 	- The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
	 * COPY 	- The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
	 * */
	enum class SSBOUsage {
		StreamDraw,
		StreamRead,
		StreamCopy,

		StaticDraw,
		StaticRead,
		StaticCopy,

		DynamicDraw,
		DynamicRead,
		DynamicCopy,
	};

	class SSBO {
	public:
		static std::shared_ptr<SSBO> Create();
		static std::shared_ptr<SSBO> Create(Buffer buffer, SSBOUsage usage = SSBOUsage::DynamicDraw);
		static std::shared_ptr<SSBO> Create(uint64_t size, SSBOUsage usage = SSBOUsage::DynamicDraw);

		template<typename T>
		static std::shared_ptr<SSBO> Create(const T* value, SSBOUsage usage = SSBOUsage::DynamicDraw) {return Create({const_cast<T*>(value), sizeof(T)}, usage); }
		template<typename T>
		static std::shared_ptr<SSBO> Create(const std::vector<T>& values, SSBOUsage usage = SSBOUsage::DynamicDraw) {
			void* ptr = const_cast<T*>(values.data());
			uint64_t count = values.size();
			uint64_t size = sizeof(T);
			return Create({ptr, count * size}, usage);
		}
	public:
		SSBO();
		SSBO(Buffer buffer, SSBOUsage usage = SSBOUsage::DynamicDraw);
		SSBO(uint64_t size, SSBOUsage usage = SSBOUsage::DynamicDraw);
		~SSBO();

		SSBO(const SSBO&) = delete;
		SSBO& operator=(const SSBO&) = delete;

	public:
		void Bind(uint32_t index);
		// void Unbind();

		[[nodiscard]] uint32_t GetRendererID() const;
	private:
		void Allocate(Buffer buffer, SSBOUsage usage = SSBOUsage::DynamicDraw);
		void Allocate(uint64_t size, SSBOUsage usage = SSBOUsage::DynamicDraw);

		template<typename T>
		void Allocate(const T* data, SSBOUsage usage = SSBOUsage::DynamicDraw);

		template<typename T>
		void AllocateArray(uint64_t count, SSBOUsage usage = SSBOUsage::DynamicDraw);

		/**
		 * Set data inside an already allocated SSBO.
		 * @param buffer The data we want to put inside the SSBO.
		 * @param offset The offset inside the SSBO (if we only want to update a part of it.)
		 */
		void SetData(Buffer buffer, int64_t offset = 0);

		template<typename T>
		void SetData(const T* data, int64_t offset = 0);

		template<typename T>
		void SetArray(const T* data, uint64_t count, int64_t offset = 0);

		template<typename T>
		void SetVector(const std::vector<T>& data, int64_t offset = 0);

		template<typename T>
		void SetElementInArray(const T* element, int64_t index, int64_t rawOffset = 0);
	private:
		uint32_t m_RendererID{~0u};
	};

	template<typename T>
	void SSBO::Allocate(const T *data, SSBOUsage usage) {
		Allocate({const_cast<T*>(data), sizeof(T)}, usage);
	}

	template<typename T>
	void SSBO::SetElementInArray(const T *element, int64_t index, int64_t rawOffset) {
		SetData(tr::Buffer{const_cast<T*>(element), sizeof(T)}, rawOffset + index * sizeof(T));
	}

	template<typename T>
	void SSBO::SetVector(const std::vector<T> &data, int64_t offset) {
		SetData(tr::Buffer{const_cast<T*>(data.data()), data.size() * sizeof(T)}, offset);
	}

	template<typename T>
	void SSBO::SetArray(const T *data, uint64_t count, int64_t offset) {
		SetData(tr::Buffer{const_cast<T*>(data), sizeof(T) * count}, offset);
	}

	template<typename T>
	void SSBO::SetData(const T *data, int64_t offset) {
		SetData(tr::Buffer{const_cast<T*>(data), sizeof(T)}, offset);
	}

	template<typename T>
	void SSBO::AllocateArray(uint64_t count, SSBOUsage usage) {
		Allocate({nullptr, count * sizeof(T)}, usage);
	}
} // tr

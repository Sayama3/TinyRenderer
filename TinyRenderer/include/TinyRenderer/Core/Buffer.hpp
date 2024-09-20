//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "Logger.hpp"
#include <cstdint>
#include <memory>

namespace tr {


	// Non Owning Buffer
	struct Buffer {
	public:
		Buffer() = default;
		Buffer(const Buffer&) = default;
		Buffer& operator=(const Buffer&) = default;
		~Buffer() = default;
		Buffer(void* data, uint64_t size);
		Buffer(uint64_t size);

		template<typename T>
		static Buffer Create(T* data, uint64_t count)
		{
			return Buffer{data, count * sizeof(T)};
		}
	public:
		static Buffer Copy(const Buffer& other);

		void Allocate(uint64_t size);
		void Release();
		void Clear();

		template<typename T>
		T* As();

		template<typename T>
		const T* As() const;

		template<typename T>
		T& At(uint64_t index);

		template<typename T>
		const T& At(uint64_t index) const;

		template<typename T>
		T& operator[](uint64_t i);

		template<typename T>
		const T& operator[](uint64_t i) const;

		uint8_t* data = nullptr;
		uint64_t size = 0;
	};

	template<typename T>
	const T &Buffer::At(uint64_t index) const {
		TR_ASSERT(data, "Buffer is empty - has no initialized data.");
		TR_ASSERT(size >= (index+1) * sizeof(T), "Cannot access index {0} for type {1}. Buffer size: {2}. Required size: {3}.",
						index,
						typeid(T).name(),
						size,
						(index+1) * sizeof(T));
		return ((T*)data)[index];
	}

	template<typename T>
	T &Buffer::At(uint64_t index) {
		TR_ASSERT(data, "Buffer is empty - has no initialized data.");
		TR_ASSERT(size >= (index+1) * sizeof(T), "Cannot access index {0} for type {1}. Buffer size: {2}. Required size: {3}.",
						index,
						typeid(T).name(),
						size,
						(index+1) * sizeof(T));
		return ((T*)data)[index];
	}

	template<typename T>
	T *Buffer::As() {
		TR_ASSERT(sizeof(T) >= size, "The size {} is not big enough to be cast as {}({} bytes)", size, typeid(T).name(), sizeof(T));
		return reinterpret_cast<T*>(data);
	}

	template<typename T>
	const T *Buffer::As() const {
		TR_ASSERT(sizeof(T) >= size, "The size {} is not big enough to be cast as {}({} bytes)", size, typeid(T).name(), sizeof(T));
		return reinterpret_cast<T*>(data);
	}

	template<typename T>
	T& Buffer::operator[](uint64_t i) {
		TR_ASSERT((i + 1) * sizeof(T) > size, "The size {} is too small to access the index {} of type {}", size, i, typeid(T).name());
		return reinterpret_cast<T*>(data)[i];
	}

	template<typename T>
	const T& Buffer::operator[](uint64_t i) const {
		TR_ASSERT((i + 1) * sizeof(T) > size, "The size {} is too small to access the index {} of type {}", size, i, typeid(T).name());
		return reinterpret_cast<const T*>(data)[i];
	}

} // tr

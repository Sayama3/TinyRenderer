//
// Created by Sayama on 12/09/2024.
//

#include "TinyRenderer/Core/Buffer.hpp"

namespace tr
{
	Buffer::Buffer(void *data, uint64_t size) : data(reinterpret_cast<uint8_t *>(data)), size(size) {}

	Buffer::Buffer(uint64_t size) {
		Allocate(size);
	}

	Buffer Buffer::Copy(const Buffer &other) {
		Buffer buff(other.size);
		memcpy(buff.data, other.data, other.size);
		return buff;
	}

	void Buffer::Allocate(uint64_t size) {
		Release();

		this->data = static_cast<uint8_t*>(malloc(size));
		this->size = size;
	}

	void Buffer::Release() {
		if (this->data)
		{
			free(this->data);
			this->data = nullptr;
			this->size = 0u;
		}
	}

	void Buffer::Clear() {
		data = nullptr;
		size = 0;
	}

}
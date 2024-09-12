//
// Created by Sayama on 12/09/2024.
//

#pragma once

#include "Texture.hpp"
#include "TinyRenderer/Core/Image.hpp"
#include <array>
#include <filesystem>


namespace tr {

	struct CubemapSpecification
	{
		inline CubemapSpecification() = default;
		inline ~CubemapSpecification() = default;

		uint32_t width = 0, height = 0, channels = 0;

		TextureFilter filterMag = TextureFilter::Linear;
		TextureFilter filterMin = TextureFilter::Linear;

		TextureWrapper wrapperS = TextureWrapper::ClampToEdge;
		TextureWrapper wrapperT = TextureWrapper::ClampToEdge;
		TextureWrapper wrapperR = TextureWrapper::ClampToEdge;

		PixelFormat pixelFormat = PixelFormat::RGB;
		PixelType pixelType = PixelType::PX_8;
	};


	class Cubemap
	{
	public:
		enum Side : uint8_t
		{
			Right,
			Left,
			Top,
			Bottom,
			Front,
			Back,
		};
	public:
		Cubemap(const CubemapSpecification& spec);
		~Cubemap();
		Cubemap(const Cubemap&) = delete;
		Cubemap& operator=(const Cubemap&) = delete;
	public:
		static std::shared_ptr<Cubemap> Load(const std::filesystem::path& path);
	public:
		void Bind(uint32_t slot = 0);
		static void Unbind();
		[[nodiscard]] uint32_t GetRendererID() const;

		void SetData(Side side, const Image& image);
		void SetData(const std::array<Image, 6>& images);
	private:
		CubemapSpecification m_Specification;
		uint32_t m_RendererID = 0;
	};

} // tr

//
// Created by Sayama on 12/09/2024.
//

#include "TinyRenderer/Renderer/Cubemap.hpp"
#include "TinyRenderer/Core/Logger.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace tr {
	class CubemapSpecHelper
	{
	private:
		CubemapSpecification& spec;
	public:
		CubemapSpecHelper(CubemapSpecification& specification) : spec(specification) {}
		~CubemapSpecHelper() = default;

		[[nodiscard]] GLenum GetInternalFormat() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.pixelFormat) {
				case RED:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_R8;
						case PX_16: return GL_R16;

						case PX_8UI: return GL_R8UI;
						case PX_16UI: return GL_R16UI;
						case PX_32UI: return GL_R32UI;

						case PX_8I: return GL_R8I;
						case PX_16I: return GL_R16I;
						case PX_32I: return GL_R32I;

						case PX_16F: return GL_R16F;
						case PX_32F: return GL_R32F;
					}
				}
				case RG:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RG8;
						case PX_16: return GL_RG16;

						case PX_8UI: return GL_RG8UI;
						case PX_16UI: return GL_RG16UI;
						case PX_32UI: return GL_RG32UI;

						case PX_8I: return GL_RG8I;
						case PX_16I: return GL_RG16I;
						case PX_32I: return GL_RG32I;

						case PX_16F: return GL_RG16F;
						case PX_32F: return GL_RG32F;
					}
				}
				case RGB:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RGB8;
						case PX_16: return GL_RGB16;

						case PX_8UI: return GL_RGB8UI;
						case PX_16UI: return GL_RGB16UI;
						case PX_32UI: return GL_RGB32UI;

						case PX_8I: return GL_RGB8I;
						case PX_16I: return GL_RGB16I;
						case PX_32I: return GL_RGB32I;

						case PX_16F: return GL_RGB16F;
						case PX_32F: return GL_RGB32F;
					}
				}
				case RGBA:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RGBA8;
						case PX_16: return GL_RGBA16;

						case PX_8UI: return GL_RGBA8UI;
						case PX_16UI: return GL_RGBA16UI;
						case PX_32UI: return GL_RGBA32UI;

						case PX_8I: return GL_RGBA8I;
						case PX_16I: return GL_RGBA16I;
						case PX_32I: return GL_RGBA32I;

						case PX_16F: return GL_RGBA16F;
						case PX_32F: return GL_RGBA32F;
					}
				}
			}

			TR_WARNING("No valid internal format found. Defaulting to GL_R8.");
			return GL_R8;
		}

		[[nodiscard]] GLenum GetFormat() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.pixelFormat) {
				case RED: return GL_RED;
				case RG: return GL_RG;
				case RGB: return GL_RGB;
				case RGBA: return GL_RGBA;
			}

			TR_ASSERT(false, "The pixel format {0} do not exist...", (int)spec.pixelType);
			return GL_RGBA;
		}

		[[nodiscard]] GLenum GetType() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.pixelType) {
				case PX_8: return GL_UNSIGNED_BYTE;
				case PX_16: return GL_UNSIGNED_SHORT;
				case PX_8UI: return GL_UNSIGNED_BYTE;
				case PX_16UI: return GL_UNSIGNED_SHORT;
				case PX_32UI: return GL_UNSIGNED_INT;
				case PX_8I: return GL_BYTE;
				case PX_16I: return GL_SHORT;
				case PX_32I: return GL_INT;
				case PX_16F: return GL_HALF_FLOAT;
				case PX_32F: return GL_FLOAT;
			}

			TR_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return GL_UNSIGNED_BYTE;
		}

		[[nodiscard]] std::string_view GetTypeToString() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.pixelType) {
				case PX_8: return "PX_8";
				case PX_16: return "PX_16";
				case PX_8UI: return "PX_8UI";
				case PX_16UI: return "PX_16UI";
				case PX_32UI: return "PX_32UI";
				case PX_8I: return "PX_8I";
				case PX_16I: return "PX_16I";
				case PX_32I: return "PX_32I";
				case PX_16F: return "PX_16F";
				case PX_32F: return "PX_32F";
			}

			TR_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return "Unknown";
		}

		[[nodiscard]] uint32_t GetPixelSize() const {
			TR_PROFILE_FUNCTION();
			switch (spec.pixelType) {
				case PX_8:
				case PX_8UI:
				case PX_8I:
					return 1U;
				case PX_16:
				case PX_16UI:
				case PX_16I:
				case PX_16F:
					return 2U;
				case PX_32UI:
				case PX_32I:
				case PX_32F:
					return 4U;
			}

			TR_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return 1U;
		}

		[[nodiscard]] GLint GetMagFilter() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.filterMag) {

				case Nearest: return GL_NEAREST;
				case Linear: return GL_LINEAR;
			}
			TR_WARNING("No value found for MagFilter, defaulting to 'Linear'.");
			return GL_LINEAR;
		}

		[[nodiscard]] GLint GetMinFilter() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.filterMin) {

				case Nearest: return GL_NEAREST;
				case Linear: return GL_LINEAR;
			}
			TR_WARNING("No value found for MinFilter, defaulting to 'Linear'.");
			return GL_LINEAR;
		}

		[[nodiscard]] GLint GetWrapS() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.wrapperS) {
				case Repeat: return GL_REPEAT;
				case ClampToEdge: return GL_CLAMP_TO_EDGE;
				case MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
			TR_WARNING("No value found for WrapS, defaulting to 'Repeat'.");
			return GL_REPEAT;
		}

		[[nodiscard]] GLint GetWrapT() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.wrapperT) {
				case Repeat: return GL_REPEAT;
				case ClampToEdge: return GL_CLAMP_TO_EDGE;
				case MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
			TR_WARNING("No value found for WrapT, defaulting to 'Repeat'.");
			return GL_REPEAT;
		}

		[[nodiscard]] GLint GetWrapR() const
		{
			TR_PROFILE_FUNCTION();
			switch (spec.wrapperR) {
				case Repeat: return GL_REPEAT;
				case ClampToEdge: return GL_CLAMP_TO_EDGE;
				case MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
			TR_WARNING("No value found for WrapT, defaulting to 'Repeat'.");
			return GL_REPEAT;
		}
	};

	[[nodiscard]] GLint GetOpenGLSide(Cubemap::Side side)
	{
		switch (side) {
			case Cubemap::Side::Right: return 0;	// GL_TEXTURE_CUBE_MAP_POSITIVE_X
			case Cubemap::Side::Left: return 1;		// GL_TEXTURE_CUBE_MAP_NEGATIVE_X
			case Cubemap::Side::Top: return 2;		// GL_TEXTURE_CUBE_MAP_POSITIVE_Y
			case Cubemap::Side::Bottom: return 3;	// GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
			case Cubemap::Side::Front: return 4;	// GL_TEXTURE_CUBE_MAP_POSITIVE_Z
			case Cubemap::Side::Back: return 5;		// GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		}
	}

	Cubemap::Cubemap(const CubemapSpecification& spec) : m_Specification(spec)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_RendererID);
		CubemapSpecHelper helper(m_Specification);

		TR_ASSERT(m_Specification.channels > 0 && m_Specification.channels < 5, "The number of channel {0} is not handle at the moment.", m_Specification.channels);

		glTextureStorage2D(
				m_RendererID,
				1,           // one level, no mipmaps
				helper.GetInternalFormat(),    // internal format
				static_cast<GLint>(m_Specification.width),
				static_cast<GLint>(m_Specification.height));

		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, helper.GetMagFilter());
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, helper.GetMinFilter());

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, helper.GetWrapS());
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, helper.GetWrapT());
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, helper.GetWrapR());
	}

	Cubemap::~Cubemap()
	{
		TR_CHECK(m_RendererID, "The cubemap wasn't created.");
		if(m_RendererID) {
			glDeleteTextures(1, &m_RendererID);
			m_RendererID = 0;
		}
	}

	void Cubemap::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Cubemap::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	uint32_t Cubemap::GetRendererID() const
	{
		return m_RendererID;
	}

	void Cubemap::SetData(const std::array<Image, 6>& images)
	{
		for (uint8_t i = 0; i < 6; ++i) {
			SetData(Side(i), images[i]);
		}
	}

	void Cubemap::SetData(Side side, const Image& data)
	{
		CubemapSpecHelper helper(m_Specification);

		// Separate assertions for width, height and channels
		TR_ASSERT(data.width == m_Specification.width, "Image width ({0}) is different from the texture width ({1})", data.width, m_Specification.width);
		TR_ASSERT(data.height == m_Specification.height, "Image height ({0}) is different from the texture height ({1})", data.height, m_Specification.height);
		TR_ASSERT(data.channels == m_Specification.channels, "Image channels ({0}) is different from the texture channels ({1})", data.channels, m_Specification.channels);

		// Assertion for data size
		TR_ASSERT(data.source.size == m_Specification.width * m_Specification.height * m_Specification.channels * helper.GetPixelSize(), "The size of the image ({0}) is different from the calculated texture size using width, height, channels and pixel type ('{1}')", data.source.size, helper.GetTypeToString());

		GLenum dataFormat = helper.GetFormat();
		GLenum pixelType = helper.GetType();

		glTextureSubImage3D(
				m_RendererID,
				0,      // only 1 level in example
				0,
				0,
				GetOpenGLSide(side),   // the offset to desired cubemap face, which offset goes to which face above
				static_cast<GLint>(m_Specification.width),
				static_cast<GLint>(m_Specification.height),
				1,      // depth how many faces to set, if this was 3 we'd set 3 cubemap faces at once
				dataFormat,
				pixelType,
				data.source.data);
	}

	std::shared_ptr<Cubemap> Cubemap::Load(const std::filesystem::path &path)
	{
		TR_PROFILE_FUNCTION();
		Image source;
		std::array<Image, 6> images;
		CubemapSpecification spec;
		stbi_set_flip_vertically_on_load(false);

		int width, height, channels;
		std::string strPath = path.string();

		if(!std::filesystem::exists(path)) {
			TR_ERROR("The file {0} do not exist.", strPath);
			return nullptr;
		}

		uint8_t* raw = nullptr;
		{
			TR_PROFILE_SCOPE("ImportTexture2D - stbi_load");
			raw = stbi_load(strPath.c_str(), &width, &height, &channels, 0);
		}

		if(!raw) {
			TR_ERROR("Load of cubemap '{0}' failed.\n{1}.", strPath, stbi_failure_reason());
			return nullptr;
		}

		//TODO: Handle HDR ?
		source.Reset(raw, width, height, channels);
		raw = nullptr;

		spec.channels = channels;
		spec.pixelType = PixelType::PX_8;
		spec.pixelFormat = static_cast<PixelFormat>(channels);

		uint32_t textureSize = 0;
		if(width > height) {
			if (width / 4 == height / 3) {
				textureSize = height / 3;

				images[Cubemap::Top   ] = source.Splice(textureSize * 1, textureSize * 0, textureSize, textureSize);
				images[Cubemap::Left  ] = source.Splice(textureSize * 0, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Front ] = source.Splice(textureSize * 1, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Right ] = source.Splice(textureSize * 2, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Back  ] = source.Splice(textureSize * 3, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Bottom] = source.Splice(textureSize * 1, textureSize * 2, textureSize, textureSize);

			} else {
				TR_ERROR("Invalid cubemap dimensions: {0}x{1}.", width, height);
				return nullptr;
			}
		} else /*width < height*/{
			if (width / 3 == height / 4) {
				textureSize = height / 4;

				images[Cubemap::Top   ] = source.Splice(textureSize * 1, textureSize * 0, textureSize, textureSize);
				images[Cubemap::Left  ] = source.Splice(textureSize * 0, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Front ] = source.Splice(textureSize * 1, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Right ] = source.Splice(textureSize * 2, textureSize * 1, textureSize, textureSize);
				images[Cubemap::Back  ] = source.Splice(textureSize * 1, textureSize * 3, textureSize, textureSize);
				images[Cubemap::Bottom] = source.Splice(textureSize * 1, textureSize * 2, textureSize, textureSize);
			} else {
				TR_ERROR("Invalid cubemap dimensions: {0}x{1}.", width, height);
				return nullptr;
			}
		}
		spec.width = textureSize;
		spec.height = textureSize;

		std::shared_ptr<Cubemap> cm = std::make_shared<Cubemap>(spec);
		cm->SetData(images);

		return cm;
	}
} // tr
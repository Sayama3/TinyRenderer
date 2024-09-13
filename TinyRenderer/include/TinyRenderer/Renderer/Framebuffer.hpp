//
// Created by Sayama on 12/09/2024.
//

#pragma once

#include <cstdint>
#include <vector>

namespace tr {

	enum class FramebufferTarget : int8_t
	{
		None = -1,
		ReadAndWrite = 0,
		Read,
		Write,
	};

	enum class FramebufferTextureFormat
	{
		None = 0,
		// Color
		RGBA8,
		RGBA16,
		RED_INTEGER,

		// Depth/Stencil
		DEPTH24STENCIL8,

		//Default
		Color = RGBA8,
		Depth = DEPTH24STENCIL8,
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		inline FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat;
		//TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		inline FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : Attachments(attachments) {}
		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		FramebufferAttachmentSpecification Attachements;

		//TODO: add format.
		bool SwapChainTarget = false;

		FramebufferSpecification() = default;
		inline FramebufferSpecification(uint32_t width, uint32_t height) : Width(width), Height(height) {}
		inline FramebufferSpecification(uint32_t width, uint32_t height, std::initializer_list<FramebufferTextureSpecification> attachments) : Width(width), Height(height), Attachements(std::move(attachments)) {}
	};

	class Framebuffer
	{
	private:
		void Invalidate();
	public:
		Framebuffer(const FramebufferSpecification& specification);
		~Framebuffer();
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& specification) {return  std::make_shared<Framebuffer>(specification);}
	public:
		const FramebufferSpecification& GetSpecification() const;

		void Bind(FramebufferTarget target = FramebufferTarget::ReadAndWrite);
		void Unbind();
		void Resize(uint32_t width, uint32_t height);
		int ReadPixel(uint32_t index, int x, int y);
		uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const;
		uint32_t GetDepthAttachmentRendererID() const;

		void ClearColorAttachment(uint32_t index, uint8_t value);
		void ClearColorAttachment(uint32_t index, uint32_t value);
		void ClearColorAttachment(uint32_t index, int value);
		void ClearColorAttachment(uint32_t index, float value);
	private:
		FramebufferSpecification m_Specification;
		uint32_t m_RendererID = 0;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;
		FramebufferTarget m_BindTarget{FramebufferTarget::None};
	};

} // tr

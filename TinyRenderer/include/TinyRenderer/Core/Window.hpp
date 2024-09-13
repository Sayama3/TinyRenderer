//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "TinyRenderer/Events/Event.hpp"

namespace tr {

	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		WindowProps(std::string title = "Application", uint32_t width = 1600, uint32_t height = 900) : Title(std::move(title)), Width(width), Height(height) {}
		WindowProps(const WindowProps&) = default;
		WindowProps& operator=(const WindowProps&) = default;
		WindowProps(WindowProps&& other)  noexcept : Title(std::move(other.Title)), Width(other.Width), Height(other.Height) {}
		WindowProps& operator=(WindowProps&& other) noexcept
		{
			swap(other);
			return *this;
		}

		void swap(WindowProps& other)
		{
			std::swap(Title, other.Title);
			std::swap(Width, other.Width);
			std::swap(Height, other.Height);
		}
	};

	class Window {
	public:
		struct Data
		{
			std::string Title;
			uint32_t Width, Height;
			bool Minified;
			bool VSync;

			EventCallBackFn  EventCallback = nullptr;
		};
	public:
		Window(WindowProps props);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	public:
		void SwapBuffers();
		void PollEvents();
		void SetVSync(bool state);
		void Close();

		void SetEventCallback(const EventCallBackFn& callback);

		[[nodiscard]] bool ShouldClose() const;
		[[nodiscard]] void* GetNativeWindow() {return m_Window;}
		[[nodiscard]] const void* GetNativeWindow() const {return m_Window;}

		template<typename T>
		[[nodiscard]] inline T* GetNative() {return static_cast<T*>(m_Window);}
		template<typename T>
		[[nodiscard]] inline const T* GetNative() const {return static_cast<const T*>(m_Window);}
	private:
		void* m_Window = nullptr;
		WindowProps m_WindowProps;
		Data m_Data;
	};

} // tr

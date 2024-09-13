//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Window.hpp"
#include "TinyRenderer/Core/Logger.hpp"
#include "TinyRenderer/Events/ApplicationEvent.hpp"
#include "TinyRenderer/Events/KeyEvent.hpp"
#include "TinyRenderer/Events/MouseEvent.hpp"

#include <cstdint>
#include <string>
#include <iostream>

#include <glad/glad.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include <GLFW/glfw3.h>

namespace tr {
	enum GLFWKeyState : int {
		PRESS = GLFW_PRESS,
		RELEASE = GLFW_RELEASE,
		REPEAT = GLFW_REPEAT,
	};

	static void glfw_error_callback(int error_code, const char* description)
	{
		TR_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window::Window(WindowProps props) : m_WindowProps(std::move(props))
	{
		m_Data.Title = m_WindowProps.Title;
		m_Data.Width = m_WindowProps.Width;
		m_Data.Height = m_WindowProps.Height;
		m_Data.Minified = false;

		TR_TRACE("Creating window {}", m_WindowProps.Title);
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit()) {
			TR_ERROR("GLFW could not be initialized.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		// Create window with graphics context
		m_Window = glfwCreateWindow(m_WindowProps.Width, m_WindowProps.Height, m_WindowProps.Title.c_str(), nullptr, nullptr);
		if (m_Window == nullptr) {
			TR_ERROR("GLFW could not Create a window.");
			return;
		}

		// Set OpenGL Context
		{
			glfwMakeContextCurrent(reinterpret_cast<GLFWwindow *>(m_Window));
			int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
			TR_INFO("glad loading status: {0}", status);

			TR_INFO("OpenGL Info:");
			TR_INFO("  Vendor: {0}", (const char *) glGetString(GL_VENDOR));
			TR_INFO("  Renderer: {0}", (const char *) glGetString(GL_RENDERER));
			TR_INFO("  Version: {0}", (const char *) glGetString(GL_VERSION));
		}

		glfwSetWindowUserPointer(GetNative<GLFWwindow>(), &m_Data);
		SetVSync(m_Data.VSync);

		// Set GLFW Callbacks
		glfwSetFramebufferSizeCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, int width, int height)
		{
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowIconifyCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, int iconify)
		{
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);
			data.Minified = iconify == GLFW_TRUE;

			WindowMinifyEvent event(iconify == GLFW_TRUE);
			data.EventCallback(event);
			;        });

		glfwSetWindowCloseCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window)
		{
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			switch ((GLFWKeyState)action) {
				case GLFWKeyState::PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::REPEAT:
				{
					// Can be extract if we want the number of repeat/
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, unsigned int codepoint){
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, int button, int action, int mods)
		{
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			switch ((GLFWKeyState)action) {
				case GLFWKeyState::PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case REPEAT:
				{
					MouseButtonRepeatEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, double xoffset, double yoffset){
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(GetNative<GLFWwindow>(), [](GLFWwindow* window, double xpos, double ypos){
			Window::Data& data = *(Window::Data*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			data.EventCallback(event);
		});
	}

	Window::~Window()
	{
		if(m_Window) {
			glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_Window));
			glfwTerminate();
			m_Window = nullptr;
		}
	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(m_Window));
	}

	void Window::PollEvents() {
		glfwPollEvents();
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(const_cast<GLFWwindow*>(reinterpret_cast<GLFWwindow*>(m_Window)));
	}

	void Window::SetVSync(bool state) {
		glfwSwapInterval(state ? 1 : 0); // Enable vsync
	}
	void Window::Close() {
		TR_TRACE("Closing window {}", m_WindowProps.Title);
		glfwSetWindowShouldClose(reinterpret_cast<GLFWwindow*>(m_Window), true);
	}

	void Window::SetEventCallback(const EventCallBackFn &callback)
	{
		m_Data.EventCallback = callback;
	}
} // tr
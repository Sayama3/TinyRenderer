//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Window.hpp"
#include "TinyRenderer/Core/Logger.hpp"
#include <cstdint>
#include <string>
#include <iostream>

#include "glad/glad.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include "GLFW/glfw3.h"

namespace tr {

	static void glfw_error_callback(int error, const char* description)
	{
		std::cerr << "GLFW Error " << error << " : " << description << std::endl;
	}

	Window::Window(WindowProps props) : m_WindowProps(std::move(props))
	{
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

		glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_Window));
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TR_INFO("glad loading status: {0}", status);

		TR_INFO("OpenGL Info:");
		TR_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		TR_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		TR_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
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
} // tr
//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Application.hpp"
#include "TinyRenderer/Core/Utility.hpp"
#include "TinyRenderer/Renderer/Renderer.hpp"
#include "TinyRenderer/Events/ApplicationEvent.hpp"


#include "glad/glad.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include "GLFW/glfw3.h"

namespace tr {
	Application::Application(WindowProps windowProps)
	{
		m_Window = std::make_unique<Window>(std::move(windowProps));
		m_Window->SetEventCallback(TR_BIND_MEMBER_FN(Application::OnEvent));
		m_Window->SetEventCallback([this](::tr::Event& e) { this->OnEvent(e);});
		InitializeRenderer();
	}

	Application::~Application() {
		TerminateRenderer();
		m_Window.reset();
	}

	bool Application::ShouldRun()
	{
		return !m_Window->ShouldClose();
	}

	void Application::BeginFrame()
	{
		m_Window->PollEvents();
	}

	void Application::EndFrame()
	{
		m_Window->SwapBuffers();
	}
	uint32_t Application::GetWindowWidth() const
	{
		return m_Window->GetWidth();
	}
	uint32_t Application::GetWindowHeight() const
	{
		return m_Window->GetHeight();
	}

	void Application::Close()
	{
		m_Window->Close();
	}

	void Application::InitializeRenderer()
	{
		Renderer::Initialize();
	}

	void Application::TerminateRenderer()
	{
		Renderer::Terminate();
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_MEMBER_FN(Application::OnWindowResize));

		for (auto* callback : m_Events)
		{
			if(!callback) continue;
			(*callback)(e);
			if(e.m_Handled) {
				break;
			}
		}
	}


	bool Application::OnWindowResize(WindowResizeEvent &e)
	{
		if(e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			return false;
		}


		// Resizing the renderer only if we got a valid width & height.
//		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::AddCallback(Callback* fn)
	{
		m_Events.emplace_back(fn);
	}

	void Application::RemoveCallback(Callback* fn)
	{
		auto it = std::find(m_Events.begin(), m_Events.end(),fn);
		if(it != m_Events.end()) {
			m_Events.erase(it);
		}
	}

} // tr
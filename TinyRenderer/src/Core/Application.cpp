//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Application.hpp"
#include "TinyRenderer/Renderer/Renderer.hpp"


namespace tr {
	Application::Application(WindowProps windowProps)
	{
		m_Window = std::make_unique<Window>(std::move(windowProps));
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
		Clear();
	}

	void Application::EndFrame()
	{
		m_Window->SwapBuffers();
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

	void Application::Clear() {
		Renderer::Clear();
	}

} // tr
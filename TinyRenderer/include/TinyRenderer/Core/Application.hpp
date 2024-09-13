//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "Window.hpp"
#include "TinyRenderer/Events/Event.hpp"
#include "TinyRenderer/Events/Callback.hpp"
#include "TinyRenderer/Events/ApplicationEvent.hpp"
#include <memory>

namespace tr {

	class Application {
	public:
		Application(WindowProps windowProps);
		~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	public:
		bool ShouldRun();
		void Close();

		void BeginFrame();
		void EndFrame();

		[[nodiscard]] uint32_t GetWindowWidth() const;
		[[nodiscard]] uint32_t GetWindowHeight() const;
	public:
		void AddCallback(Callback* fn);
		void RemoveCallback(Callback* fn);
	private:
		void OnEvent(Event& e);
		bool OnWindowResize(tr::WindowResizeEvent &e);
	private:
		void InitializeRenderer();
		void TerminateRenderer();
	private:
		std::vector<Callback*> m_Events;
		std::unique_ptr<Window> m_Window{nullptr};
	};

} // tr

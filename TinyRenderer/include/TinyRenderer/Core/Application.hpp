//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include "Window.hpp"
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
	private:
		void InitializeRenderer();
		void TerminateRenderer();
		void Clear();
	private:
		std::unique_ptr<Window> m_Window{nullptr};
	};

} // tr

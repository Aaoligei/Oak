#pragma once
#include "Events/Event.h"
#include "Window.h"
#include"Core.h"
#include "Events/ApplicationEvent.h"

namespace Oak {
	class OAK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};
	Application* CreateApplication();
}


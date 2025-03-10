#pragma once
#include "Events/Event.h"
#include "Window.h"
#include"Core.h"

namespace Oak {
	class OAK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}


#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Oak {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		OAK_TRACE(e);

		while (true);
	}
}
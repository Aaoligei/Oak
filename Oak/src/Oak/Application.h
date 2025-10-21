#pragma once
#include "Events/Event.h"
#include "Window.h"
#include"Core.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include"imgui/ImGuiLayer.h"
#include"./Renderer/Shader.h"
#include"./Renderer/Buffer.h"
#include "./Renderer/VertexArray.h"
#include"./Renderer/OrthographicCamera.h"

namespace Oak {
	class OAK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);

	};
	Application* CreateApplication();
}


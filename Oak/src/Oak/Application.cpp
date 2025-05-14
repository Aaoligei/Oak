#include"glad/glad.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <GLFW/glfw3.h>



namespace Oak {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		OAK_CORE_ASSERT(!s_Instance, "Application already exists")
			s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		//bind VAO,VBO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices)));

		std::string vertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			out vec3 ourColor;
			void main()
			{
				gl_Position = vec4(aPos, 1.0);
				ourColor=aPos;
			}
		)";

		std::string fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;
			in vec3 ourColor;
			void main()
			{
				
				FragColor = vec4(ourColor.xy+0.5,ourColor.z, 1.0);
			}
		)";
		m_Shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_EBO->GetCount(), GL_UNSIGNED_INT, 0);


			for (Layer* layer : m_LayerStack) 
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		OAK_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
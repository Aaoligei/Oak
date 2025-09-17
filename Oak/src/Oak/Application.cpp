#include"glad/glad.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include"Renderer/RenderCommand.h"
#include"Renderer/Renderer.h"


namespace Oak {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static uint32_t GetTypeToGLType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}
		OAK_CORE_ASSERT(false, "Unknown ShaderDataType !");
		return 0;
	}

	Application::Application():
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
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

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices)));

		//set layout
		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPos"}
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);

		std::string vertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			out vec3 ourColor;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader,m_VAO);

			Renderer::EndScene();

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
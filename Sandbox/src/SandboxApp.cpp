#include<Oak.h>
#include "imgui/imgui.h"

class ExampleLayer : public Oak::Layer
{
public:
    ExampleLayer()
        :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
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

		m_VAO.reset(Oak::VertexArray::Create());
		m_VBO.reset(Oak::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_EBO.reset(Oak::IndexBuffer::Create(indices, sizeof(indices)));

		//set layout
		Oak::BufferLayout layout = {
			{ Oak::ShaderDataType::Float3, "aPos"}
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
		m_Shader = std::make_unique<Oak::Shader>(vertexShaderSource, fragmentShaderSource);
    }

    void OnUpdate() override
    {
		Oak::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Oak::RenderCommand::Clear();

		m_Camera.SetRotation(45.f);
		Oak::Renderer::BeginScene(m_Camera);

		Oak::Renderer::Submit(m_Shader, m_VAO);

		Oak::Renderer::EndScene();
    }


    virtual void OnImGuiRender() override
    {
        
    }

    void OnEvent(Oak::Event& event) override
    {
        OAK_TRACE("{0}", event);
    }
private:
    std::shared_ptr<Oak::VertexArray> m_VAO;
    std::shared_ptr<Oak::VertexBuffer> m_VBO;
    std::shared_ptr<Oak::IndexBuffer> m_EBO;
    std::shared_ptr<Oak::Shader> m_Shader;

    Oak::OrthographicCamera m_Camera;
};


class Sandox :public Oak::Application {
public:
	Sandox() {
        PushLayer(new ExampleLayer());
	}
	
	~Sandox() {

	}
};

Oak::Application* Oak::CreateApplication() {
	return new Sandox();
}
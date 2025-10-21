#include "oakpch.h"
#include"Renderer.h"
#include"RenderCommand.h"

namespace Oak {
	
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UpdateUniformMat4("u_ViewProjection", m_SceneData->ViewProjection);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
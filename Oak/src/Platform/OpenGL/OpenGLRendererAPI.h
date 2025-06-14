#pragma once

#include"./Renderer/RendererAPI.h"

namespace Oak{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() = default;

	private:
		// ͨ�� RendererAPI �̳�
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};
}

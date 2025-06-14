#pragma once

#include<glm/glm.hpp>
#include"VertexArray.h"

namespace Oak{
	class RendererAPI
	{
	public:
		enum class API {
			None = 0, OpenGL = 1, DirectX = 2
		};

		static RendererAPI* Create();

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_RendererAPI; }
		inline static void SetAPI(API api) { s_RendererAPI = api; }

	private:
		static API s_RendererAPI;

	};
}

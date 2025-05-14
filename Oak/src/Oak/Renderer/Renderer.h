#pragma once
#include"../oakpch.h"

namespace Oak {
	enum RendererApi {
		None = 0,OpenGL=1
	};

	class Renderer
	{
	public:
		inline static RendererApi GetApi() { return s_RendererAPI; }
	private:
		static RendererApi s_RendererAPI;
	};
}
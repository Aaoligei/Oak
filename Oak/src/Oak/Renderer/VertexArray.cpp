#include"VertexArray.h"
#include"../Platform/OpenGL/OpenGLVertexArray.h"
#include"Renderer.h"

namespace Oak {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetApi())
		{
		case RendererApi::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererApi::OpenGL:  return new OpenGLVertexArray();

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
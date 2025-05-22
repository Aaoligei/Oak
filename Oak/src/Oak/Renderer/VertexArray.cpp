#include"VertexArray.h"
#include"../Platform/OpenGL/OpenGLVertexArray.h"
#include"RendererAPI.h"

namespace Oak {
	VertexArray* VertexArray::Create() {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		case RendererAPI::API::DirectX:    OAK_CORE_ASSERT(false, "RendererAPI::DirectX is not supported!"); return nullptr;

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
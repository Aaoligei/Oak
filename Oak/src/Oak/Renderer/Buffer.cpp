#include"Buffer.h"
#include"../Platform/OpenGL/OpenGLBuffer.h"

#include"./Renderer/Renderer.h"
namespace Oak {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetApi()) {
		case RendererApi::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererApi::OpenGL:  return new OpenGLVertexBuffer(vertices, size);

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		
		switch (Renderer::GetApi()) {
		case RendererApi::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererApi::OpenGL:  return new OpenGLIndexBuffer(indices, count);

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
}
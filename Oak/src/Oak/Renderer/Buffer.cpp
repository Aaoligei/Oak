#include "oakpch.h"
#include"Buffer.h"
#include"../Platform/OpenGL/OpenGLBuffer.h"

#include"./Renderer/RendererAPI.h"
namespace Oak {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::DirectX: OAK_CORE_ASSERT(false, "RendererAPI::DirectX is not supported!"); return nullptr;

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:    OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::API::DirectX: OAK_CORE_ASSERT(false, "RendererAPI::DirectX is not supported!"); return nullptr;

		}
		OAK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
}
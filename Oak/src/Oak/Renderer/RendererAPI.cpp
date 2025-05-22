#include"RendererAPI.h"
#include"../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Oak {

	RendererAPI::API RendererAPI::s_RendererAPI = RendererAPI::API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		API api = GetAPI();
		switch (api) {
		case API::None : OAK_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case API::OpenGL: return new OpenGLRendererAPI();
		case API::DirectX: OAK_CORE_ASSERT(false, "RendererAPI::DirectX is not supported!"); return nullptr;
		}
	}

}
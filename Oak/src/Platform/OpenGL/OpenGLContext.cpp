#include"glad/glad.h"
#include"../oakpch.h"
#include "OpenGLContext.h"
#include"Core.h"
#include"Log.h"

Oak::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
{
	m_WindowHandle = windowHandle;
	OAK_CORE_ASSERT(windowHandle, "Window handle is null!");
	OAK_CORE_INFO("OpenGL context created");

}

void Oak::OpenGLContext::Init()
{

    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    OAK_CORE_ASSERT(status, "Failed to initialize GLAD");

	OAK_CORE_INFO("OpenGL Info:");
	OAK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	OAK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	OAK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	OAK_CORE_INFO("  GLSL Version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));

}

void Oak::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

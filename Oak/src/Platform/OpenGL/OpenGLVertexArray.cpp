#include "OpenGLVertexArray.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>

Oak::OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

void Oak::OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void Oak::OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void Oak::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
{ 
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout.GetElements())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.Count, element.GLType, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
		index++;
	}
	m_VertexBuffers.push_back(vertexBuffer);
}

void Oak::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}

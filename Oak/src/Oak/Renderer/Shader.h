#pragma once
#include<string>

#include<glm/glm.hpp>

namespace Oak {
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UpdateUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};

}

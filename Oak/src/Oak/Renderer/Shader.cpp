#include"oakpch.h"
#include"Shader.h"
#include <glad/glad.h>

Oak::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	// 创建一个空的顶点着色器句柄
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 将顶点着色器源代码发送给GL
	// 注意std::string的.c_str是NULL字符终止的。
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// 编译顶点着色器
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength包括NULL字符
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// 我们不再需要这个着色器了。
		glDeleteShader(vertexShader);

		// 你可以根据需要使用infoLog。
		OAK_CORE_ERROR("顶点着色器编译失败：");
		OAK_CORE_ERROR("{0}", infoLog.data());
		return;
	}

	// 创建一个空的片段着色器句柄
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 将片段着色器源代码发送给GL
	// 注意std::string的.c_str是NULL字符终止的。
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// 编译片段着色器
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength包括NULL字符
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// 我们不再需要这个着色器了。
		glDeleteShader(fragmentShader);
		// 不要泄漏着色器。
		glDeleteShader(vertexShader);

		// 你可以根据需要使用infoLog。
		OAK_CORE_ERROR("片段着色器编译失败：");
		OAK_CORE_ERROR("{0}", infoLog.data());
		return;
	}

	// 顶点着色器和片段着色器已成功编译。
	// 现在是将它们链接到一个程序的时候了。
	// 获取一个程序对象。
	GLuint program = glCreateProgram();
	m_RendererID = program;

	// 将我们的着色器附加到我们的程序
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// 链接我们的程序
	glLinkProgram(program);

	// 注意这里使用的是glGetProgram*而不是glGetShader*。
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength包括NULL字符
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// 我们不再需要这个程序了。
		glDeleteProgram(program);
		// 不要泄漏着色器。
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// 你可以根据需要使用infoLog。
		OAK_CORE_ERROR("着色器链接失败：");
		OAK_CORE_ERROR("{0}", infoLog.data());
		return;
	
	}
}

Oak::Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Oak::Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Oak::Shader::UnBind() const
{
	glUseProgram(0);
}

void Oak::Shader::UpdateUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	uint32_t location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

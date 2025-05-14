#include"Shader.h"
#include"../oakpch.h"
#include <glad/glad.h>

Oak::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	// ����һ���յĶ�����ɫ�����
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// ��������ɫ��Դ���뷢�͸�GL
	// ע��std::string��.c_str��NULL�ַ���ֹ�ġ�
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// ���붥����ɫ��
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength����NULL�ַ�
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// ���ǲ�����Ҫ�����ɫ���ˡ�
		glDeleteShader(vertexShader);

		// ����Ը�����Ҫʹ��infoLog��
		OAK_CORE_ERROR("������ɫ������ʧ�ܣ�");
		OAK_CORE_ERROR("{0}", infoLog.data());
		return;
	}

	// ����һ���յ�Ƭ����ɫ�����
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ��Ƭ����ɫ��Դ���뷢�͸�GL
	// ע��std::string��.c_str��NULL�ַ���ֹ�ġ�
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// ����Ƭ����ɫ��
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength����NULL�ַ�
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// ���ǲ�����Ҫ�����ɫ���ˡ�
		glDeleteShader(fragmentShader);
		// ��Ҫй©��ɫ����
		glDeleteShader(vertexShader);

		// ����Ը�����Ҫʹ��infoLog��
		OAK_CORE_ERROR("Ƭ����ɫ������ʧ�ܣ�");
		OAK_CORE_ERROR("{0}", infoLog.data());
		return;
	}

	// ������ɫ����Ƭ����ɫ���ѳɹ����롣
	// �����ǽ��������ӵ�һ�������ʱ���ˡ�
	// ��ȡһ���������
	GLuint program = glCreateProgram();
	m_RendererID = program;

	// �����ǵ���ɫ�����ӵ����ǵĳ���
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// �������ǵĳ���
	glLinkProgram(program);

	// ע������ʹ�õ���glGetProgram*������glGetShader*��
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// maxLength����NULL�ַ�
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// ���ǲ�����Ҫ��������ˡ�
		glDeleteProgram(program);
		// ��Ҫй©��ɫ����
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// ����Ը�����Ҫʹ��infoLog��
		OAK_CORE_ERROR("��ɫ������ʧ�ܣ�");
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

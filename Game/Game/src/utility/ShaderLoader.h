#pragma once
#include <GL/glew.h>
class Shader
{
private:
	GLuint m_ShaderID = 0;
	const char* m_VertPath, * m_FragPath;
public:
	Shader(const char* vertPath, const char* fragPath) :m_VertPath(vertPath), m_FragPath(fragPath)
	{
		glewInit();
		m_ShaderID = load();
	}
	~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	void enable() const {
		glUseProgram(m_ShaderID);
	}

	void disable() const {
		glUseProgram(0);
	}
	inline GLuint getProgram()
	{
		return m_ShaderID;
	}
private:
	GLuint load() {
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = read_file(m_VertPath);
		std::string fragSourceString = read_file(m_FragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		int result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result != true)
		{
			int length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Engine Shader ERROR: Failed to compile vertex shader!\n" << error.data() << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result != true)
		{
			int length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Engine Shader ERROR: Failed to compile fragment shader!\n" << error.data() << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}
};
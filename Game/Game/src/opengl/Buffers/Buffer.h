#pragma once
#include "GL/glew.h"
class Buffer
{
private:
	GLuint m_BufferID;
	GLuint m_ComponentCount;
public:
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
		:m_ComponentCount(componentCount)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}
	void unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline GLuint getComponentCount()const { return m_ComponentCount; }

};
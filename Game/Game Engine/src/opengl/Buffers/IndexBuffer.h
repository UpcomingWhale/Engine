#pragma once
#include<GL/glew.h>
class IndexBuffer
{
private:
	GLuint m_BufferID;
	GLuint m_Count;
public:
	IndexBuffer(GLushort* data, GLsizei count)
		:m_Count(count)
	{

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}
	void unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	inline GLuint getCount() { return m_Count; }
};
#pragma once
#include <GL/glew.h>
class VertexArray
{
private:
	GLuint m_ArrayID;
	std::vector<Buffer*> m_Buffers;
public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}
	~VertexArray()
	{
		for (int i = 0; i < m_Buffers.size(); i++)
			delete m_Buffers[i];
	}

	void addBuffer(Buffer * buffer, GLuint index)
	{
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, false, 0, 0);



		buffer->unbind();
		unbind();
	}
	void bind() const
	{
		glBindVertexArray(m_ArrayID);
	}
	void unbind() const
	{
		glBindVertexArray(0);
	}

};
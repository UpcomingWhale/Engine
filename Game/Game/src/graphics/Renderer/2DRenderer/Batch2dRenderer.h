#pragma once
#include "include.h"

#define MAX_SPRITES		1000
#define VERTEX_SIZE		sizeof(VertexData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		SPRITE_SIZE*MAX_SPRITES
#define INDICES_SIZE	MAX_SPRITES*6

#define VERTEX_INDEX	0
#define COLOR_INDEX		1
#define TEXCORD_INDEX	2
#define TID_INDEX		3

class Renderer2D
{
public:
	Renderer2D()
	{
		init();
	}
	void begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	void submit(const Square* renderable)
	{

		const vec3 position = vec3(renderable->getPosition().x, renderable->getPosition().y, renderable->getPosition().z);
		const vec2& size = renderable->getSize();
		const vec4& color = renderable->getColor();
		const std::vector<vec2>& uv = renderable->getUV();
		const GLuint tid = renderable->getTexID();
		float ts = 0.0f;
		unsigned int c = 0;
		if (tid > 0)
		{
			bool found = false;
			for (int i = 0; i < m_TexSlots.size(); i++)
			{
				if (m_TexSlots[i] == tid)
				{
					ts = (float)(i + 1);

					found = true;

					break;
				}
			}
			if (!found)
			{
				if (m_TexSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				m_TexSlots.push_back(tid);
				ts = (float)(m_TexSlots.size() - 1);
			}

		}
		else {

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.a * 255.0f;

			c = a << 24 | b << 16 | g << 8 | r;
		}

		m_Buffer->vertex = position;
		m_Buffer->color = c;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = ts;
		m_Buffer++;

		m_Buffer->vertex = vec3(position.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer->uv = uv[1];
		m_Buffer->tid = ts;
		m_Buffer++;

		m_Buffer->vertex = vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer->uv = uv[2];
		m_Buffer->tid = ts;
		m_Buffer++;

		m_Buffer->vertex = vec3(position.x + size.x, position.y, position.z);
		m_Buffer->color = c;
		m_Buffer->uv = uv[3];
		m_Buffer->tid = ts;
		m_Buffer++;

		indexCount += 6;
	}
	void flush()
	{
		for (int i = 0; i < m_TexSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TexSlots[i]);
		}
		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);
		indexCount = 0;
	}
	void init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		glVertexAttribPointer(TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(TID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);
		glEnableVertexAttribArray(TEXCORD_INDEX);
		glEnableVertexAttribArray(TID_INDEX);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		GLushort indices[INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;

		}

		m_IBO = new IndexBuffer(indices, INDICES_SIZE);
		glBindVertexArray(0);

	}
private:
	GLuint m_VAO;
	GLuint m_VBO;
	IndexBuffer* m_IBO;
	GLsizei indexCount;

	VertexData* m_Buffer;

	std::vector<GLuint> m_TexSlots;
};

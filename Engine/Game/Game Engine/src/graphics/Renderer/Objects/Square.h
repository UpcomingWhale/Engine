#pragma once
#include "include.h"

struct VertexData
{
	vec3 vertex;
	vec2 uv;
	float tid;
	unsigned int color;
};




class Square
{
protected:
	vec4 m_Position;
	vec2 m_Size;
	vec4 m_Color;
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	GLuint textureID = 0;
	std::vector<vec2> m_UV;

	float velocity = 0;


	GLuint count;
	bool colX = false;
	bool colY = false;

	vec2 screenPos;
public:
	Square(vec4 position, vec2 size, vec4 color, Texture* texture)
		:m_Position(position), m_Size(size), m_Color(color)
	{
		if (texture != NULL)
		{
			textureID = texture->getTexID();
		}
		
		m_VertexArray = new VertexArray();
		screenPos.x = position.x;
		screenPos.y = position.y;
		GLfloat vertices[] = {
			0, 0, 0,
			0, size.y, 0,
			size.x, size.y, 0,
			size.x, 0, 0
		};

		GLfloat colors[] =
		{
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a
		};
		GLfloat texCoords[]
		{
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f
			
		};
		
		m_UV.push_back(vec2(0.0f, 1.0f));
		m_UV.push_back(vec2(0.0f, 0.0f));
		m_UV.push_back(vec2(1.0f, 0.0f));
		m_UV.push_back(vec2(1.0f, 1.0f));


		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		m_VertexArray->addBuffer(new Buffer(texCoords, 2 * 4, 2), 2);
		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
		count = m_IndexBuffer->getCount();
	}

	virtual ~Square()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

	inline const VertexArray* getVAO() const { return m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
	inline const GLuint getCount() const { return count; }

	inline const  vec4& getPosition() const { return m_Position; }
	inline const  vec2& getSize() const { return m_Size; }
	inline const  vec4& getColor() const { return m_Color; }
	void changeXPos(int x) { m_Position.x = x; }
	void changeYPos(int y) { m_Position.y = y; }
	bool isColX() { return colX; }
	bool isColY() { return colY; }
	void setColX(bool x) { colX = x; };
	void setColY(bool y) { colY = y; }

	inline const std::vector<vec2>& getUV() const { return m_UV; }
	inline const GLuint getTexID() const { return textureID; }
	vec2 getScreenPos() { return screenPos; }
	void changeScreenPosX(float x) { screenPos.x = x; }
	void changeScreenPosY(float y) { screenPos.y = y; }
	void setVelocity(float v) { velocity = v; }
	float getVelocity() { return velocity; }

};
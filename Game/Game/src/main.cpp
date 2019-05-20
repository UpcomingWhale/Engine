#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <deque>
#include "stb_image.h"
#include <Windows.h>
 

inline float toRadians(float degree)
{
	return (float)(degree * (M_PI / 180.0f));
}

class Window {

public:

	Window(int width, int height, const char* title)
		:p_Width(width), p_Height(height)
	{
		glewInit();
		glfwInit();
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwSwapInterval(0); 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwMakeContextCurrent(window);
	}
	~Window() {}

	bool ShouldClose()
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			return true;
		return false;
	}

	void update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	GLFWwindow* getWindow() { return window; }
private:

	int p_Height,
		p_Width;
	GLFWwindow* window;

};
static std::string read_file(const char* filepath)
{
	FILE* file = fopen(filepath, "rt");
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* data = new char[length + 1];
	memset(data, 0, length + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);
	fclose(file);

	std::string result(data);
	delete[] data;

	return result;
}

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

	void addBuffer(Buffer* buffer, GLuint index)
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

struct vec2
{
public:
	float x, y;

	vec2() = default;
	vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	friend vec2& operator+(vec2& left, const vec2& right)
	{
		return left.add(right);
	}
	friend vec2& operator-(vec2& left, const vec2& right)
	{
		return left.subtract(right);
	}
	friend vec2& operator/(vec2& left, const vec2& right)
	{
		return left.divide(right);
	}
	friend vec2& operator*(vec2& left, const vec2& right)
	{
		return left.multiply(right);
	}

private:

	vec2& add(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	vec2& subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	vec2& divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	vec2& multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

};
struct vec3
{
public:
	float x, y, z;

	vec3() = default;
	vec3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend vec3& operator+(vec3& left, const vec3& right){ return left.add(right); }
	friend vec3& operator-(vec3& left, const vec3& right) {
		return left.subtract(right);
	}
	friend vec3& operator/(vec3& left, const vec3& right) {
		return left.divide(right);
	}
	friend vec3& operator*(vec3& left, const vec3& right) {
		return left.multiply(right);
	}


private:

	vec3& add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	vec3& subtract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	vec3& divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	vec3& multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

};
struct vec4
{
public:
	float x, y, z, a;

	vec4() = default;
	vec4(const float& x, const float& y, const float& z, const float& a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

	friend vec4& operator+(vec4& left, const vec4& right) {
		return left.add(right);
	}
	friend vec4& operator-(vec4& left, const vec4& right) {
		return left.subtract(right);
	}
	friend vec4& operator/(vec4& left, const vec4& right) {
		return left.divide(right);
	}
	friend vec4& operator*(vec4& left, const vec4& right) {
		return left.multiply(right);
	}

private:

	vec4& add(const vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		a += other.a;
		return *this;
	}
	vec4& subtract(const vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		a -= other.a;
		return *this;
	}
	vec4& divide(const vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		a /= other.a;
		return *this;
	}
	vec4& multiply(const vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		a *= other.a;
		return *this;
	}

};
struct mat4
{
public:
	union
	{
		float elements[4 * 4];
		vec4 colums[4];
	};


	mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}
	mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	static mat4 identity()
	{
		return mat4(1.0f);
	}

	static mat4 orthographic(float left, float right, float bot, float top, float Near, float Far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bot);

		result.elements[2 + 2 * 4] = 2.0f / (Near - Far);


		result.elements[0 + 3 * 4] = (left + right) / (left - right);

		result.elements[1 + 3 * 4] = (bot + top) / (bot - top);

		result.elements[2 + 3 * 4] = (Far + Near) / (Far - Near);

		return result;
	}
	static mat4 perspective(float fov, float aspectRatio, float Near, float Far)
	{
		mat4 result(1.0f);

		float q = 1.0f / (float)tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (Near + Far) / (Near - Far);
		float c = (2.0f * Near * Far) / (Near - Far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = -b;
		result.elements[3 + 2 * 4] = 1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	static mat4 translation(const vec4& translation)
	{
		mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}
	static mat4 rotation(float angle, const vec3& axis)
	{
		mat4 result(1.0f);

		float r = toRadians(angle);
		float c = (float)cos(r);
		float s = (float)sin(r);
		float mc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * mc + c;
		result.elements[1 + 0 * 4] = y * x * mc + z * s;
		result.elements[2 + 0 * 4] = x * z * mc - y * s;

		result.elements[0 + 1 * 4] = x * y * mc - z * s;
		result.elements[1 + 1 * 4] = y * mc + c;
		result.elements[2 + 1 * 4] = y * z * mc + x * s;


		result.elements[0 + 2 * 4] = x * z * mc + y * s;
		result.elements[1 + 2 * 4] = y * z * mc - x * s;
		result.elements[2 + 2 * 4] = z * mc + c;

		return result;
	}
	static mat4 scale(const vec3& scale)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	friend mat4& operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

private:
	mat4& multiply(const mat4& other)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				elements[x + y * 4] = sum;
			}
		}
		return *this;
	}

};

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


class Square
{
protected:
	 vec4 m_Position;
	 vec2 m_Size;
	 vec4 m_Color;
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;

	Shader& m_Shader;

	GLuint count;
	bool colX = false;
	bool colY = false;
public:
	Square(vec4 position, vec2 size, vec4 color, Shader& shader)
		:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();

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
		GLfloat textCords[] =
		{
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};
		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		m_VertexArray->addBuffer(new Buffer(textCords, 2 * 4, 2), 2);
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
	inline Shader& getShader() const { return m_Shader; }
	inline const GLuint getCount() const { return count; }

	inline const  vec4& getPosition() const { return m_Position; }
	inline const  vec2& getSize() const { return m_Size; }
	inline const  vec4& getColor() const { return m_Color; }
	void changeXPos(float x) { m_Position.x = x; }
	void changeYPos(float y) { m_Position.y = y; }
	bool isColX() { return colX; }
	bool isColY() { return colY; }
	void setColX(bool x) { colX = x; };
	void setColY(bool y) { colY = y; }
};
class Custom2dRenderable
{
protected:
	vec4 Position;
	VertexArray* p_VertexArray;
	IndexBuffer* p_IndexBuffer;
	Shader& p_Shader;
	GLuint count;
public:
	Custom2dRenderable(vec4 position, GLfloat vertices[], GLfloat colors[],GLushort indices[], int height, int width, int rows, int iSize, Shader& shader)
		:Position(position), p_Shader(shader)
	{
		p_VertexArray = new VertexArray();

		p_VertexArray->addBuffer(new Buffer(vertices, height * width, rows), 0);
		p_VertexArray->addBuffer(new Buffer(colors, height * width, rows), 1);

		p_IndexBuffer = new IndexBuffer(indices, iSize);
		count = p_IndexBuffer->getCount();
	};
	virtual ~Custom2dRenderable()
	{
		delete p_VertexArray;
		delete p_IndexBuffer;
	}
	inline const VertexArray* getVAO() const { return p_VertexArray; }
	inline const IndexBuffer* getIBO() const { return p_IndexBuffer; }
	inline Shader& getShader() const { return p_Shader; }
	inline const GLuint getCount() const { return count; }

	inline const  vec4& getPosition() const { return Position; }
};

class Basic2DLayer
{
private:
	std::deque<const Square*> RenderQueue;
public:
	void submit(const Square* square)
	{
		RenderQueue.push_back(square);
	}
	void flush()
	{
		while (!RenderQueue.empty())
		{
			const Square* square = RenderQueue.front();
			square->getVAO()->bind();
			square->getIBO()->bind();

			square->getShader().enable();

			glUniformMatrix4fv(glGetUniformLocation(square->getShader().getProgram(), "ml_matrix"), 1, false, mat4::translation(square->getPosition()).elements);
			glDrawElements(GL_TRIANGLES, square->getCount(), GL_UNSIGNED_SHORT, nullptr);

			square->getVAO()->unbind();
			square->getIBO()->unbind();

			RenderQueue.pop_front();

		}
	}
};

class Camera {
private:
	mat4 cPosition = mat4(1.0f);
	float cOffset = 0.0f;
	int projection = 0;
	mat4 pMatrix = mat4(1.0f);
public:
	Camera(vec4 position)
	{
		cPosition = mat4::translation(position);
	}
	Camera()
	{
		
	}
	~Camera(){}

	void updateCamera(Shader shader)
	{
		shader.enable();
		if (projection == 0)
		{
			pMatrix = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 1.0f, 100.0f);
		}
		if (projection == 1)
		{
			pMatrix = mat4::perspective(90.0f, 16.0f / 9.0f, 1.0f, 100.0f);
		}
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "pr_matrix"), 1, false, pMatrix.elements);
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, cPosition.elements);
	}
	void setProjection(int n)
	{
		projection = n;
	}
};


bool CheckCollision(Square& one, Square& two)
{
	// Collision x-axis?
	bool collisionX = one.getPosition().x + one.getSize().x >= two.getPosition().x &&
		two.getPosition().x + two.getSize().x >= one.getPosition().x;
	// Collision y-axis?
	bool collisionY = one.getPosition().y + one.getSize().y >= two.getPosition().y &&
		two.getPosition().y + two.getSize().y >= one.getPosition().y;
	// Collision only if on both axes
	return collisionX && collisionY;
}
bool CheckAllCollision(Square& square,Square staticObjs[2])
{
	bool isCol;
	for (int i = 0; i < 2; i++)
	{
		if (CheckCollision(square, staticObjs[i]))
		{
			return true;
		}
	}
	return false;
}
class PhysicsEngine
{
private:
public:
	PhysicsEngine()
	{

	}
	~PhysicsEngine()
	{

	}
	void CheckCollision(Square& Player, Square staticObjs[100], int sObjCount)
	{
		for (int i = 0; i < sObjCount; i++)
		{
			if (isCollidingX(Player, staticObjs[i]) && isCollidingY(Player, staticObjs[i]))
			{
				if (staticObjs[i].isColY())
				{
					if (Player.getPosition().x < staticObjs[i].getPosition().x)
					{
						Player.changeXPos(staticObjs[i].getPosition().x - Player.getSize().x - 1.0f);
					}
					else if (Player.getPosition().x + Player.getSize().x > staticObjs[i].getPosition().x + staticObjs[i].getSize().x)
					{
						Player.changeXPos(staticObjs[i].getPosition().x + staticObjs[i].getSize().x + 1.0f);
					}
				}
				if (staticObjs[i].isColX())
				{
					if (Player.getPosition().y > staticObjs[i].getPosition().y)
					{
						Player.changeYPos(staticObjs[i].getPosition().y + staticObjs[i].getSize().y + 1.0f);
					}
					else if (Player.getPosition().y + Player.getSize().y > staticObjs[i].getPosition().y)
					{
						Player.changeYPos(staticObjs[i].getPosition().y - Player.getSize().y - 1.0f);
					}
				}
			}
			else if (isCollidingY(Player, staticObjs[i]))
			{
				staticObjs[i].setColY(true);
				staticObjs[i].setColX(false);
			}
			else if (isCollidingX(Player, staticObjs[i]))
			{
				staticObjs[i].setColX(true);
				staticObjs[i].setColY(false);
			}
			
		}
	}
private:
	bool isCollidingX(Square& one, Square& two)
	{
		// Collision x-axis?
		bool collisionX = one.getPosition().x + one.getSize().x >= two.getPosition().x &&
			two.getPosition().x + two.getSize().x >= one.getPosition().x;
		return collisionX;
	}
	bool isCollidingY(Square& one, Square& two)
	{
		// Collision y-axis?
		bool collisionY = one.getPosition().y + one.getSize().y >= two.getPosition().y &&
			two.getPosition().y + two.getSize().y >= one.getPosition().y;
		return collisionY;
	}
};

int main(int argc, char* argv[])
{

	Window window(1280, 720, "title");
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	Shader brick("shaders/brick.vert", "shaders/brick.frag");
	Shader player("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();


	int w, h, comp;
	GLuint texture;
	unsigned char* image;
	image = stbi_load("textures/yuh.jpg", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	GLuint brickTex;
	image = stbi_load("textures/brick.jfif", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	glGenTextures(1, &brickTex);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, brickTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shader.getProgram(), "texture1"), 0);
	stbi_image_free(image);
	GLuint playerText;
	image = stbi_load("textures/player.png", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	glGenTextures(1, &playerText);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, playerText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shader.getProgram(), "texture1"), 0);
	mat4 camera = mat4(1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 100.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, camera.elements);

	Square * square2 = new Square(vec4(900.0f, 300.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square * square3 = new Square(vec4(700.0f, 200.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square * square4 = new Square(vec4(400.0f, 700.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	brick.enable();

	glUniform1i(glGetUniformLocation(brick.getProgram(), "texture1"), 1);

	glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "camera"), 1, false, camera.elements);
	Square * left_wall = new Square(vec4(-100.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square * floor = new Square(vec4(0.0f, 0.0f, 3.0f, 0.0f), vec2(1000.0f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square * ceiling = new Square(vec4(0.0f, 522.5f, 3.0f, 0.0f), vec2(1000.f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square * right_wall = new Square(vec4(990.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);

	player.enable();
	glUniform1i(glGetUniformLocation(player.getProgram(), "texture1"), 2);
	glUniformMatrix4fv(glGetUniformLocation(player.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(player.getProgram(), "camera"), 1, false, camera.elements);
	Square * square1 = new Square(vec4(500.0f, 41, 3.0f, 1.0f), vec2(40, 80), vec4(1.0f, 0.0f, 1.0f, 0.0f), player);

	Basic2DLayer layer1;
	float cameraX = 0.0f;
	float cameraY = 0.0f;
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	double x = 500;
	double y = 0;

	Square staticObjs[7] = { *square2, *square3, *square4, *left_wall, *floor, *ceiling, *right_wall };


	PhysicsEngine pEngine;

	while (!window.ShouldClose())
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (GetKeyState('W') & 0x8000)
		{
			square1->changeYPos(square1->getPosition().y + 1.0f);
		}
		if (GetKeyState('S') & 0x8000)
		{
			square1->changeYPos(square1->getPosition().y - 1.0f);
		}
		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			

				if(x > 800)
				{
					cameraX += -1.0f;
					square1->changeXPos(square1->getPosition().x + 1.0f);
				}
				else
				{
					x += 1.0f;
					square1->changeXPos(square1->getPosition().x + 1.0);
				}
		}
		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{

			if (x < 200)
			{
				cameraX += 1.0f;
				square1->changeXPos(square1->getPosition().x - 1.0);
			}
			else
			{
				x += -1.0f;
				square1->changeXPos(square1->getPosition().x - 1.0);
			}
		}

		pEngine.CheckCollision(*square1,staticObjs, 7); 
		player.enable();
		glUniformMatrix4fv(glGetUniformLocation(player.getProgram(), "camera"), 1, false, camera.elements);
		layer1.submit(square1);
		shader.enable();
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, camera.elements);
		layer1.submit(square2);
		
		layer1.submit(square3);
		layer1.submit(square4);

		brick.enable();
		glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "camera"), 1, false, camera.elements);
		layer1.submit(left_wall);
		layer1.submit(floor);
		layer1.submit(right_wall);
		layer1.submit(ceiling);
		layer1.flush();

		window.update();
	}
	
	return 0;
}
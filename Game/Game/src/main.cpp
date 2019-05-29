#define _USE_MATH_DEFINES

#include "include.h"



class Engine
{
public:
	
	Engine()
	{
		glClearColor(0.5f, 0.5f, 0.5f ,1.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	};
	~Engine() {};
	void BackGroudColor(vec4 color)
	{
		m_ClearColor = color;
	}
	GLuint createTexture(const char* src, int slot, int wrapType) //wrap type uses OpenGL #defines (GL_CLAMP_TO_EDGE, GL_REPEAT, etc.)
	{
		GLuint texture;
		int h, w, comp;
		unsigned char* image = stbi_load(src, &w, &h, &comp, STBI_rgb_alpha);
		
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texture);

		if (wrapType != NULL)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);
		return texture;
		
	}

	void bindTexture(Shader* shader, int slot)
	{
		shader->enable();
		glUniform1i(glGetUniformLocation(shader->getProgram(), "texture1"), slot);
	}

	void updateShader(Shader *shader, const char* uniform, mat4 elements)
	{
		
		shader->enable();
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), uniform), 1, false, elements.elements);

	}
private:

	vec4 m_ClearColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

};

int main(int argc, char* argv[])
{
	Window window(1280,720,"title");
	Engine* engine = new Engine;
	Shader shader("shaders/basic.vert", "shaders/basic.frag");

	unsigned char* image;
	int h, w, comp;
	GLuint texture = engine->createTexture("textures/heart.png", 0, NULL);


	GLuint brickTex = engine->createTexture("textures/brick.jfif", 1, GL_REPEAT);


	GLuint playerTex = engine->createTexture("textures/player.png", 2, GL_CLAMP_TO_BORDER);

	mat4 camera(1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 100.0f, 1.0f);

	engine->updateShader(&shader, "pr_matrix", ortho);
	engine->updateShader(&shader, "camera", camera);

	GLint texIds[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	glUniform1iv(glGetUniformLocation(shader.getProgram(), "textures"), 10, texIds);
	
	


	Square *square1 = new Square(vec4(500.0f, 41, 3.0f, 0.0f), vec2(40, 80), vec4(1.0f, 0.3f, 1.0f, 1.0f), shader, playerTex);
	Square *square2 = new Square(vec4(900.0f, 300.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square3 = new Square(vec4(400.0f, 200.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square4 = new Square(vec4(700.0f, 150.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square5 = new Square(vec4(830.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square6 = new Square(vec4(950.0f, 140.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square7 = new Square(vec4(1050.0f, 540.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, 1);
	Square* square8 = new Square(vec4(1160.0f, 40.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square9 = new Square(vec4(1260.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square10 = new Square(vec4(1400.0f, 340.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);

	

	
	
	Square* left_wall = new Square(vec4(-100.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* floor = new Square(vec4(0.0f, 0.0f, 3.0f, 0.0f), vec2(4000.0f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* ceiling = new Square(vec4(0.0f, 522.5f, 3.0f, 0.0f), vec2(4000.f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* right_wall = new Square(vec4(4000.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);

	Renderer2D layer1;
	vec2* cameraPos = new vec2;
	cameraPos->x = 0;
	cameraPos->y = 0;
	

	double x = 500;
	double y = 0;
	int change = 0;
	Square staticObjs[13] = { *square2, *square3, *square4,*square5, *square6,*square7,*square8,*square9,*square10, *left_wall, *floor, *ceiling,*right_wall };

	

	PhysicsEngine pEngine;

	while (!window.ShouldClose())
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (GetKeyState('W') & 0x8000)
		{
			square1->changeYPos(square1->getPosition().y + 5.0f);
		}
		if (GetKeyState('S') & 0x8000)
		{
			square1->changeYPos(square1->getPosition().y - 5.0f);
		}
		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			

				if(square1->getScreenPos().x > 800)
				{
					cameraPos->x += -5.0f;
					camera = mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
					square1->changeXPos(square1->getPosition().x + 5.0f);
				}
				else
				{
					square1->changeScreenPosX(square1->getScreenPos().x + 5.0f);
					square1->changeXPos(square1->getPosition().x + 5.0);
				}
		}
		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{

			if (square1->getScreenPos().x < 200)
			{
				cameraPos->x += 5.0f;
				camera = mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
				square1->changeXPos(square1->getPosition().x - 5.0);
			}
			else
			{
				square1->changeScreenPosX(square1->getScreenPos().x - 5.0f);
				square1->changeXPos(square1->getPosition().x - 5.0);
			}
		}

		pEngine.CheckCollision(*square1,staticObjs, 13, camera, *cameraPos); 

		
		engine->updateShader(&shader, "camera", camera);
		shader.enable();
		layer1.begin();
		layer1.submit(square2);
		layer1.submit(square1);
		layer1.submit(square3);
		layer1.submit(square4);
		layer1.submit(square5);
		layer1.submit(square6);
		layer1.submit(square7);
		layer1.submit(square8);
		layer1.submit(square9);
		layer1.submit(square10);

		layer1.submit(left_wall);
		layer1.submit(floor);
		layer1.submit(right_wall);
		layer1.submit(ceiling);
		layer1.end();
		layer1.flush();
		window.update();
	}
	
	return 0;
}
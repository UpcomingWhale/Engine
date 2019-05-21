#define _USE_MATH_DEFINES

#include "include.h"

int main(int argc, char* argv[])
{
	Window window(1280,720,"title");
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	Shader brick("shaders/basic.vert", "shaders/basic.frag");
	Shader player("shaders/basic.vert", "shaders/basic.frag");

	unsigned char* image;
	int h, w, comp;
	GLuint texture;

	image = stbi_load("textures/yuh.jpg", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	
	GLuint brickTex;
	
	image = stbi_load("textures/brick.jfif", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	glGenTextures(1, &brickTex);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, brickTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	GLuint playerTex;

	image = stbi_load("textures/player.png", &w, &h, &comp, STBI_rgb_alpha);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	glGenTextures(1, &playerTex);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, playerTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);



	mat4 *camera = new mat4(1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 100.0f, 1.0f);
	shader.enable();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, camera->elements);
	glUniform1i(glGetUniformLocation(shader.getProgram(), "texture1"), 0);

	brick.enable();
	glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "camera"), 1, false, camera->elements);
	glUniform1i(glGetUniformLocation(brick.getProgram(), "texture1"), 1);

	player.enable();
	glUniformMatrix4fv(glGetUniformLocation(player.getProgram(), "pr_matrix"), 1, false, ortho.elements);
	glUniformMatrix4fv(glGetUniformLocation(player.getProgram(), "camera"), 1, false, camera->elements);
	glUniform1i(glGetUniformLocation(player.getProgram(), "texture1"), 2);


	Square *square1 = new Square(vec4(500.0f, 41, 3.0f, 0), vec2(40, 80), vec4(1.0f, 0.3f, 1.0f, 1.0f), player);
	Square *square2 = new Square(vec4(900.0f, 300.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square3 = new Square(vec4(400.0f, 200.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square4 = new Square(vec4(700.0f, 150.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square5 = new Square(vec4(830.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square6 = new Square(vec4(950.0f, 140.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square7 = new Square(vec4(1050.0f, 540.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square8 = new Square(vec4(1160.0f, 40.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square9 = new Square(vec4(1260.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	Square* square10 = new Square(vec4(1400.0f, 340.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);

	

	
	
	Square* left_wall = new Square(vec4(-100.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square* floor = new Square(vec4(0.0f, 0.0f, 3.0f, 0.0f), vec2(4000.0f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square* ceiling = new Square(vec4(0.0f, 522.5f, 3.0f, 0.0f), vec2(4000.f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);
	Square* right_wall = new Square(vec4(4000.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brick);

	Basic2DLayer layer1;
	vec2* cameraPos = new vec2;
	cameraPos->x = 0;
	cameraPos->y = 0;
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double x = 500;
	double y = 0;

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
					camera = &mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
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
				camera = &mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
				square1->changeXPos(square1->getPosition().x - 5.0);
			}
			else
			{
				square1->changeScreenPosX(square1->getScreenPos().x - 5.0f);
				square1->changeXPos(square1->getPosition().x - 5.0);
			}
		}

		pEngine.CheckCollision(*square1,staticObjs, 13, *camera, *cameraPos); 

		shader.enable();
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, camera->elements);
		brick.enable();
		glUniformMatrix4fv(glGetUniformLocation(brick.getProgram(), "camera"), 1, false, camera->elements);
		player.enable();
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "camera"), 1, false, camera->elements);

		
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
		layer1.flush();
		window.update();
	}
	
	return 0;
}
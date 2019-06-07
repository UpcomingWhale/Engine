#define _USE_MATH_DEFINES

#include "include.h"

#include <chrono>



int main(int argc, char* argv[])
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Window window(1920,1080,"title");
	Shader shader("shaders/basic.vert", "shaders/basic.frag");

	Texture* texture = new Texture("textures/heart.png", NULL);


	Texture* brickTex = new Texture("textures/brick.jfif", GL_REPEAT);

	Texture* playerTex = new Texture("textures/player.png", GL_CLAMP_TO_BORDER);
	

	mat4 camera(1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 1.0f, 100.0f);

	shader.setMat4fv("pr_matrix", ortho);
	shader.setMat4fv("camera", camera);

	GLint texIds[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.set1iv("textures", 10, texIds);
	

	Square* square1 = new Square(vec4(500.0f, 41, 3.0f, 0), vec2(40, 80), vec4(1.0f, 0.3f, 1.0f, 1.0f), shader, playerTex);
	Square *square2 = new Square(vec4(900.0f, 300.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square3 = new Square(vec4(400.0f, 200.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square4 = new Square(vec4(700.0f, 150.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square5 = new Square(vec4(830.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square6 = new Square(vec4(950.0f, 140.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square7 = new Square(vec4(1050.0f, 540.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square8 = new Square(vec4(1160.0f, 40.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square9 = new Square(vec4(1260.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);
	Square* square10 = new Square(vec4(1400.0f, 340.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), shader, texture);

	Square* left_wall = new Square(vec4(-100.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* floor = new Square(vec4(0.0f, 0.0f, 3.0f, 0.0f), vec2(4000.0f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* ceiling = new Square(vec4(0.0f, 522.5f, 3.0f, 0.0f), vec2(4000.f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);
	Square* right_wall = new Square(vec4(4000.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);

	Square* background = new Square(vec4(1.0f, 0.0f, 900.0f, 0.0f), vec2(500, 500), vec4(0.2f, 0.2f, 0.2f, 1.0f), shader, brickTex);

	vec2* cameraPos = new vec2;
	cameraPos->x = 0;
	cameraPos->y = 0;
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);


	Scene* scene = new Scene();
	scene->newLayer(1);
	scene->newLayer(0);


	double x = 500;
	double y = 0;
	int change = 0;
	Square staticObjs[13] = { *square2, *square3, *square4,*square5, *square6,*square7,*square8,*square9,*square10, *left_wall, *floor, *ceiling,*right_wall };

	Square* renderables[] = { square1, square2, square3, square4, square5, square6, square7, square8, square9, square10, left_wall, right_wall, ceiling, floor };

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	PhysicsEngine pEngine;


	while (!window.ShouldClose())
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ms > 16.6)
		{

			if (GetKeyState('W') & 0x8000)
			{
				square1->changeYPos(square1->getPosition().y + SPEED);
			}
			if (GetKeyState('S') & 0x8000)
			{
				square1->changeYPos(square1->getPosition().y - SPEED);
			}
			if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{


				if (square1->getScreenPos().x > 800)
				{
					cameraPos->x += -SPEED;
					camera = mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
					scene->updateCamera(vec3(cameraPos->x, 0.0f, 0.0f));
					square1->changeXPos(square1->getPosition().x + SPEED);
				}
				else
				{
					square1->changeScreenPosX(square1->getScreenPos().x + SPEED);
					square1->changeXPos(square1->getPosition().x + SPEED);
				}
			}
			if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{

				if (square1->getScreenPos().x < 200)
				{
					cameraPos->x += SPEED;
					camera = mat4::translation(vec4(cameraPos->x, 0.0f, 0.0f, 0.0f));
					scene->updateCamera(vec3(cameraPos->x, 0.0f, 0.0f));
					square1->changeXPos(square1->getPosition().x - SPEED);
				}
				else
				{
					square1->changeScreenPosX(square1->getScreenPos().x - SPEED);
					square1->changeXPos(square1->getPosition().x - SPEED);
				}
			}

			pEngine.CheckCollision(*square1, staticObjs, 13, *scene->getCamera(), *cameraPos);
			ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}
		
		scene->submit(1, renderables, 14);
		scene->submit(0, background);
		scene->drawScene();
		window.update();
	}
	
	return 0;
}
#define _USE_MATH_DEFINES

#define TICK_RATE 1000/ 60

#include "include.h"

#include <chrono>

class Input
{
public:
	bool IsKeyPressed(GLFWwindow* window, int keycode)
	{
		bool state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool IsMouseButtonPressed(GLFWwindow* window, int button)
	{
		bool state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float GetMouseX(GLFWwindow* window)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)xpos;
	}
	float GetMouseY(GLFWwindow* window)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)ypos;
	}

};


auto currentTimeInMs()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main(int argc, char* argv[])
{
	

	Window window(1920,1080,"title");
	Shader shader("shaders/basic.vert", "shaders/basic.frag");

	Texture* texture = new Texture("textures/heart.png", NULL);


	Texture* brickTex = new Texture("textures/brick.jfif", GL_REPEAT);

	Texture* playerTex = new Texture("textures/player.png", GL_CLAMP_TO_BORDER);
	

	mat4 camera(1.0f);


	

	Square* square1 = new Square(vec4(500.0f, 41, 3.0f, 0), vec2(40, 80), vec4(1.0f, 0.3f, 1.0f, 1.0f), playerTex);
	Square *square2 = new Square(vec4(900.0f, 300.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square3 = new Square(vec4(400.0f, 200.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square4 = new Square(vec4(700.0f, 150.0f, 3.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square5 = new Square(vec4(830.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square6 = new Square(vec4(950.0f, 140.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square7 = new Square(vec4(1050.0f, 540.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f),texture);
	Square* square8 = new Square(vec4(1160.0f, 40.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square9 = new Square(vec4(1260.0f, 240.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);
	Square* square10 = new Square(vec4(1400.0f, 340.0f, 4.0f, 0.0f), vec2(70, 60), vec4(1.0f, 0.0f, 1.0f, 1.0f), texture);

	Square* left_wall = new Square(vec4(-100.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brickTex);
	Square* floor = new Square(vec4(0.0f, 0.0f, 3.0f, 0.0f), vec2(4000.0f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brickTex);
	Square* ceiling = new Square(vec4(0.0f, 522.5f, 3.0f, 0.0f), vec2(4000.f, 40.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), brickTex);
	Square* right_wall = new Square(vec4(4000.0f, 0.0f, 3.0f, 0.0f), vec2(200, 800), vec4(0.2f, 0.2f, 0.2f, 1.0f), brickTex);

	Square* background = new Square(vec4(1.0f, 0.0f, 900.0f, 0.0f), vec2(500, 500), vec4(0.2f, 0.2f, 0.2f, 1.0f), brickTex);
	vec2* cameraPos = new vec2;
	cameraPos->x = 0;
	cameraPos->y = 0;
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);


	Scene* scene = new Scene();
	int layer1 = scene->newLayer(1);
	int layer2 = scene->newLayer(0);


	double x = 500;
	double y = 0;
	int change = 0;
	Square staticObjs[13] = { *square2, *square3, *square4,*square5, *square6,*square7,*square8,*square9,*square10, *left_wall, *floor, *ceiling,*right_wall };

	Square* renderables[] = { square1, square2, square3, square4, square5, square6, square7, square8, square9, square10, left_wall, right_wall, ceiling, floor };

	auto processedTime = currentTimeInMs();

	PhysicsEngine pEngine;

	Input input;

	while (!window.ShouldClose())
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		while ((processedTime + TICK_RATE) < currentTimeInMs()) {

			if (input.IsKeyPressed(window.getWindow(), GLFW_KEY_W) == true)
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
			processedTime += TICK_RATE;
		}
		scene->submit(layer2, renderables, 14);
		scene->submit(layer1, background);
		scene->drawScene();
		window.update();
	}
	
	return 0;
}
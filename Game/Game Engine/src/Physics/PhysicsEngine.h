#pragma once
#include "include.h"



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

	void CheckCollision(Square& Player, Square staticObjs[100], int sObjCount, mat4& camera, vec2& cameraPos)
	{
		for (int i = 0; i < sObjCount; i++)
		{
			if (isCollidingX(Player, staticObjs[i]) && isCollidingY(Player, staticObjs[i]))
			{
				if (staticObjs[i].isColY())
				{
					if (Player.getPosition().x < staticObjs[i].getPosition().x)
					{
						if (Player.getScreenPos().x > 800)
						{
							cameraPos.x += SPEED;
							camera = mat4::translation(vec4(cameraPos.x, 0.0f, 0.0f, 0.0f));
							Player.changeXPos(staticObjs[i].getPosition().x - Player.getSize().x - 1.0f);

						}
						else
						{
							Player.changeScreenPosX(Player.getScreenPos().x - SPEED);
							Player.changeXPos(staticObjs[i].getPosition().x - Player.getSize().x - 1.0f);
						}
					}
					else if (Player.getPosition().x + Player.getSize().x > staticObjs[i].getPosition().x + staticObjs[i].getSize().x)
					{
						if (Player.getScreenPos().x < 200)
						{
							cameraPos.x += -SPEED;
							camera = mat4::translation(vec4(cameraPos.x, 0.0f, 0.0f, 0.0f));
							Player.changeXPos(staticObjs[i].getPosition().x + staticObjs[i].getSize().x + 1.0f);
						}
						else
						{
							Player.changeScreenPosX(Player.getScreenPos().x + SPEED);
							Player.changeXPos(staticObjs[i].getPosition().x + staticObjs[i].getSize().x + 1.0f);
						}
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

	void UpdateObj(Square& obj)
	{
		
		obj.setAcceleration(vec2(0.0f, obj.getAcceleration().y + GRAVITY));
		

	}


private:
	bool isCollidingX(Square & one, Square & two)
	{
		// Collision x-axis?
		bool collisionX = one.getPosition().x + one.getSize().x >= two.getPosition().x &&
			two.getPosition().x + two.getSize().x >= one.getPosition().x;
		return collisionX;
	}
	bool isCollidingY(Square & one, Square & two)
	{
		// Collision y-axis?
		bool collisionY = one.getPosition().y + one.getSize().y >= two.getPosition().y &&
			two.getPosition().y + two.getSize().y >= one.getPosition().y;
		return collisionY;
	}
};
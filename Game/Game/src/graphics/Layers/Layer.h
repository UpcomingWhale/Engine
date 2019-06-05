#pragma once
#include "include.h"
class Layer
{
public:

	Layer() {};
	~Layer() {};

	void submit(Square* square)
	{
		squareArray.push_back(square);
	}
	void submit(Square* squares[1000], int count)
	{
		for (int i = 0; i < count; i++)
		{
			squareArray.push_back(squares[i]);
		}
	}

	void setShader(Shader* shader)
	{
		layerShader = shader;
	}

	void drawLayer()
	{
		layerShader->enable();
		renderer->begin();
		for (int i = 0; i < squareArray.size(); i++)
		{
			renderer->submit(squareArray[i]);
		}
		renderer->end();
		renderer->flush();
		squareArray.clear();
		layerShader->disable();
	}

private:

	BatchRenderer2D* renderer = new BatchRenderer2D();
	std::vector<Square*> squareArray;
	Shader* layerShader = nullptr;
};
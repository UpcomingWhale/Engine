#pragma once
#include "include.h"

class Scene
{
public:

	Scene()
	{
		uiLayer = newLayer(0);
	};
	~Scene() {};

	int newLayer(int proj)
	{
		Layers.push_back(new Layer());
		if (proj == 0)
			Layers[Layers.size() - 1]->getShader()->setMat4fv("pr_matrix", ortho);
		if (proj == 1)
			Layers[Layers.size() - 1]->getShader()->setMat4fv("pr_matrix", persp);
		Layers[Layers.size() - 1]->getShader()->set1iv("textures", 10, texIds);
		return Layers.size() - 1;
	};
	void submit(int index, Square * square)
	{
		Layers[index]->submit(square);
	}
	void submit(int index, Square * square[], int count)
	{
		Layers[index]->submit(square, count);
	}
	void updateLight(vec2 pos)
	{
		light_pos = pos;
	}
	void drawScene()
	{
		for (int i = 0; i < Layers.size(); i++)
		{
			Layers[i]->getShader()->setMat4fv("camera", *camera);
			Layers[i]->getShader()->set2f("light_pos", light_pos);
			Layers[i]->drawLayer();
		}
	}

	void updateCamera(vec3 position)
	{
		*camera = mat4::translation(vec4(position.x, position.y, position.z, 0.0f));
	}

	mat4* getCamera() const { return camera; }

	int getUILayer() const { return uiLayer; }

private:

	std::vector<Layer*> Layers;

	GLint texIds[10] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	mat4* camera = new mat4(1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 1000.0f, 0.0f, 562.5f, 100.0f, 1.0f);
	mat4 persp = mat4::perspective(90.0f, 16.0f / 9.0f, 1.0f, 1000.0f);
	int uiLayer;
	vec2 light_pos;
};
#pragma once
#define SPEED 20.0f
#define TICK_RATE 1000/ 60


#define BIT(x) (1 << x)


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <deque>
#include "stb_image.h"
#include <Windows.h>



#include "graphics/Window/Window.h"
#include "utility/FileReader.h"

#include "opengl/Buffers/Buffer.h"
#include "opengl/Buffers/IndexBuffer.h"
#include "opengl/Buffers/VertexArray.h"

#include "Maths/eMaths.h"

#include "Physics/Physics.h"

#include "utility/Shader.h"
#include "graphics/Textures/Textures.h"


#include "graphics/Renderer/Objects/Square.h"

#include "graphics/Renderer/2DRenderer/Virtual2DRenderer.h"
#include "graphics/Renderer/2DRenderer/Batch2dRenderer.h"

#include "graphics/Layers/Layer.h"

#include "graphics/Scene/Scene.h"


#include "Physics/PhysicsEngine.h"


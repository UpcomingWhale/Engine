#pragma once
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

#include "utility/ShaderLoader.h"

#include "graphics/Renderer/Objects/Square.h"

#include "graphics/Renderer/2DRenderer/2dRenderer.h"
#include "graphics/Renderer/2DRenderer/Batch2dRenderer.h"

#include "Physics/PhysicsEngine.h"
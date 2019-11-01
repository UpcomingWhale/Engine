#pragma once
#include "include.h"

class Renderer2D
{
protected:
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void submit(const Square* renderable) = 0;
	virtual void flush() = 0;
};
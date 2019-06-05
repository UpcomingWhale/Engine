#pragma once
#include "include.h"
class Basic2DLayer : public Renderer2D
{
private:
	std::deque<const Square*> RenderQueue;
public:
	void submit(const Square* square) override
	{
		RenderQueue.push_back(square);
	}
	void flush() override
	{
		while (!RenderQueue.empty())
		{
			const Square* square = RenderQueue.front();
			square->getVAO()->bind();
			square->getIBO()->bind();

			square->getShader().enable();

			glUniformMatrix4fv(glGetUniformLocation(square->getShader().getProgram(), "ml_matrix"), 1, false, mat4::translation(square->getPosition()).elements);
			glDrawElements(GL_TRIANGLES, square->getCount(), GL_UNSIGNED_SHORT, nullptr);

			square->getVAO()->unbind();
			square->getIBO()->unbind();

			RenderQueue.pop_front();

		}
	}
};
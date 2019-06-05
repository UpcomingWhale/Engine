#pragma once
#include "include.h"

class Texture
{
public:

	Texture(const char* src, int wraptype)
	{
		GLuint texture;
		int h, w, comp;
		unsigned char* image = stbi_load(src, &w, &h, &comp, STBI_rgb_alpha);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		if (wraptype != NULL)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraptype);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wraptype);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);

		m_Texture = texture;
	}

	GLuint getTexID() const { return m_Texture; }

private:

	GLuint m_Texture;

};
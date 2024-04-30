#pragma once
#include "GLAD/glad.h"
#include "stb_image.h"

#include <iostream>

namespace GE {
	class Texture 
	{
	public:
		Texture(const char* texturePath, GLenum format);
		~Texture();

		void Bind();
		void Bind(GLenum target);
		void UnBind();
	private:
		unsigned int texture_ID;
		int width, height, nrChannels;
	};
}
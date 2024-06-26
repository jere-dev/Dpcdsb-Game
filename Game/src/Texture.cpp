#include "Texture.h"

namespace GE {
	Texture::Texture(const char* texturePath, GLenum format)
	{
		glGenTextures(1, &texture_ID);
		glBindTexture(GL_TEXTURE_2D, texture_ID);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load and generate the texture
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture_ID);
	}

	void Texture::Bind(GLenum target)
	{
		glActiveTexture(target);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
	}

	void Texture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture_ID);
	}

}
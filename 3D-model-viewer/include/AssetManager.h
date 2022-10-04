#pragma once
#include <GL/glew.h>
#include "stb_image.h"

#include <string>

namespace AssetManager
{

	static unsigned char* LoadImage(char* path) {
		int width, height, numComp;
		unsigned char *image;

		image = stbi_load(path, &width, &height, &numComp, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);

		return nullptr;
	};

};
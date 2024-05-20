#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum texSlot, GLenum format, GLenum pixelType)
{
	type = texType;
	int imageWidth, imageHeight, colorCh;

	// loading image
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &imageWidth, &imageHeight, &colorCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(texSlot);
	glBindTexture(texType, ID);
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// if you want to use GL_TEXTURE_BORDER_COLOR YOU ALSO NEED THESE 
	// float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParamerfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);


	// assign the image to OPENGL Testure object 
	glTexImage2D(texType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	// delete image when it's set in the texture object
	stbi_image_free(bytes);

	// unbind it so it cant be accidentally modified

	glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include<stb/stb_image.h>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"



int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = 
	{ 
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	GLuint indicies[] = {
		0,2,1,
		0,3,2
	};
 
	// create window Whoot!! //
	GLFWwindow* window = glfwCreateWindow(800, 800,"OpenGL Tests", NULL, NULL);

	if (!window) {
		std::cout << "No Window dude!" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// OpenGL 

	gladLoadGL();

	// Says where to render open gl within our window
	// cooordinates ar from bottom left to top right
	glViewport(0, 0, 800, 800);
	//load the shaders
	Shader shaderProgram("default.vert", "default.frag");

	// generate Vertex array  Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// generate Vertex Buffer Object and link it to verticeis
	VBO VBO1(vertices, sizeof(vertices));
	// generate Element Array Object and link it to indicies
	EBO EBO1(indicies, sizeof(indicies));

	// Links VAO to VBO
	VAO1.LinkAttribute(VBO1,0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//Unbind the thingies
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	// get the uniform location for scale
	GLint uniformID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture 


	Texture block("marioQuestionmark.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	block.texUnit(shaderProgram, "tex0", 0);








	
	


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		// access uniforms only after activating the shader programm
		glUniform1f(uniformID, 0.5f);
		block.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// dont forget to swap buffers to actually display the image
		glfwSwapBuffers(window);


		glfwPollEvents();


	}




	// Destroy before exit
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	block.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

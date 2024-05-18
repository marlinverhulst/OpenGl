#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // low left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // top 
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // innner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //  inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down 
	};

	GLuint indicies[] = {
		0, 3, 5, // lower left
		3, 2, 4, // lower right
		5, 4, 1 // top
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
	VAO1.LinkVBO(VBO1,0);

	//Unbind the thingies
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();



	
	


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// dont forget to swap buffers to actually display the image
		glfwSwapBuffers(window);


		glfwPollEvents();


	}




	// Destroy before exit
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

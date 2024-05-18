#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";






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

	//  Get References to OpenGl shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//FEED THE SHARER THE SOURCE AND COMPILE SHADER
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//WRAP them in a shader program

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//AFTER Linking it WE CAN DELETE THE SHADERS 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// CREATE vertex [Array] buffers because sending sutff from cpu to gpu is slow so we send in big batches
	//Vertex buffer object is actualy an array of references but we only have one object atm so....
	
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO); // this should come before VBO
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	


	// Store the vertices in the VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// bind the index buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// Set up the attib pointer and enable it 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// UnBind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//ClearBuffer with collor navy blue

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// dont forget to swap buffers to actually display the image
		glfwSwapBuffers(window);


		glfwPollEvents();


	}




	// Destroy before exit
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

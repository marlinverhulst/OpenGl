#include "shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//  Get References to OpenGl shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//FEED THE SHARER THE SOURCE AND COMPILE SHADER
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	compileError(vertexShader, "VERTEX");
	glCompileShader(fragmentShader);
	compileError(fragmentShader, "FRAGMENT");

	//WRAP them in a shader program

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileError(ID, "PROGRAM");

	//AFTER Linking it WE CAN DELETE THE SHADERS 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileError(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char log[1024];
	if (type != "PROGRAM") 
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, log);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
			std::cout << "Logging:" << log << "\n" << std::endl;
		}

	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, log);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
			std::cout << "Logging:" << log << "\n" << std::endl;
		}
	}
}




#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

Shaders g_shaders;

void Shaders::Init(){
	shader1.Load("shader1");
}


std::string ReadWholeFile(std::string filename){
	std::stringstream ss;
	std::ifstream f(filename);

	if(f.is_open()){
		while(!f.eof()){
			std::string buf;
			f >> buf;
			ss << buf << "\n";
		}
	}

	return ss.str();
}

bool CreateShader(GLuint* dest, GLint type, std::string filename){
	bool status = true;

	GLuint shader = 0;

	GLint result = GL_FALSE;
	int logLength;

	std::string contents = ReadWholeFile(filename);

	if(contents.size() == 0){
		std::cout << "Shader file not found: " << filename << "\n";
		status = false;
	}

	if(status){
		shader = glCreateShader(type);
		const char* contentsStr = contents.c_str();
		int contentsLength = (int) contents.size();
		glShaderSource(shader, 1, &contentsStr, &contentsLength);
		glCompileShader(shader);

		static constexpr size_t MaxLogLength = 1024;
		char buf[MaxLogLength];
		GLsizei len = 0;
		glGetShaderInfoLog(shader, MaxLogLength, &len, buf);
		if(len > 0){
			std::cout << "Shader compilation failed: " << filename << "\n";
			std::cout << buf;
			status = false;
			glDeleteShader(shader);
		}
	}

	if(status){
		*dest = shader;
	}

	return status;
}

// Uses shaderName.vert and shaderName.frag
//
bool Shader::Load(const char* shaderName){

	bool status = true;

	GLuint vertexShader, fragmentShader;
	bool vertexShaderMade = false, fragmentShaderMade = false;

	if(status){
		status = CreateShader(&vertexShader, GL_VERTEX_SHADER, std::string(shaderName) + ".vert");
	}

	if(status){
		vertexShaderMade = true;

		status = CreateShader(&fragmentShader, GL_FRAGMENT_SHADER, std::string(shaderName) + ".frag");
	}

	if(status){
		fragmentShaderMade = true;

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		static constexpr size_t MaxLogLength = 1024;
		char buf[MaxLogLength];
		GLsizei len = 0;
		glGetProgramInfoLog(program, MaxLogLength, &len, buf);
		if(len > 0){
			std::cout << "Shader link failed: " << shaderName << "\n";
			std::cout << buf;
			status = false;
			glDeleteProgram(program);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	if(vertexShaderMade)
		glDeleteShader(vertexShader);
	if(fragmentShaderMade)
		glDeleteShader(fragmentShader);

	if(status){
		mvpLoc = glGetUniformLocation(program, "mvp");
	}

	return status;
}

void Shader::Use(){
	glUseProgram(program);
}


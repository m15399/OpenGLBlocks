
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

Shaders g_shaders;

Shader* Shader::currShader = nullptr;


void Shaders::Init(){
	// Load all shaders from SHADER_LIST
	//
	#define LOAD_SHADER(name) \
		name.Load(#name);

	SHADER_LIST(LOAD_SHADER);

	#undef LOAD_SHADER
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

// Uses Shaders/shaderName.vert and Shaders/shaderName.frag
//
bool Shader::Load(const char* shaderName){

	bool status = true;

	// TODO Windows platform paths
	std::string shaderBasePath = std::string("Shaders/") + shaderName;

	GLuint vertexShader, fragmentShader;
	bool vertexShaderMade = false, fragmentShaderMade = false;

	if(status){
		status = CreateShader(&vertexShader, GL_VERTEX_SHADER, shaderBasePath + ".vert");
	}

	if(status){
		vertexShaderMade = true;

		status = CreateShader(&fragmentShader, GL_FRAGMENT_SHADER, shaderBasePath + ".frag");
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
		#define LOCATE_ATTRIBUTE(name) \
			name##Loc = glGetAttribLocation(program, #name);

		SHADER_ATTRIB_LIST(LOCATE_ATTRIBUTE);

		#undef LOCATE_ATTRIBUTE

		#define LOCATE_UNIFORM(name) \
			name##Loc = glGetUniformLocation(program, #name);

		SHADER_UNIFORM_LIST(LOCATE_UNIFORM);

		#undef LOCATE_UNIFORM
	}

	return status;
}

void Shader::Use(){
	if(!bound){
		glUseProgram(program);

		if(currShader)
			currShader->Unuse();

		bound = true;
		currShader = this;
	}
}

void Shader::Unuse(){
	bound = false;
}

void Shader::EnableAttribs(){

	#define ENABLE_ATTRIB(name) \
		{ \
			int loc = name##Loc; \
			if(loc != -1){ \
				glEnableVertexAttribArray(loc); \
			} \
		}

	SHADER_ATTRIB_LIST(ENABLE_ATTRIB);

	#undef ENABLE_ATTRIB
}

void Shader::DisableAttribs(){
	#define DISABLE_ATTRIB(name) \
		{ \
			int loc = name##Loc; \
			if(loc != -1){ \
				glDisableVertexAttribArray(loc); \
			} \
		}

	SHADER_ATTRIB_LIST(DISABLE_ATTRIB);

	#undef DISABLE_ATTRIB
}

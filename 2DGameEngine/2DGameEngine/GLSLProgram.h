#pragma once
#include <string>
#include <fstream>
#include <GL/glew.h>
#include "ErrorManager.h"

class GLSLProgram
{
public:
	GLSLProgram();
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void linkShaders();
	void use();
	void unuse();
	GLint getUniformLocation(const std::string& uniformName);
	GLint getUniformBlockIndex(const std::string& blockName);
	GLuint getPID();
private:
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};


#include "GLSLProgram.h"
#include <vector>
GLSLProgram::GLSLProgram() :_programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	//first vertex shader
	
	//creating shader context
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!_vertexShaderID) {
		ErrorManager::error("Error in vertex shader creating");
	}
	//file reading
	std::ifstream shaderFile(vertexShaderFilePath);
	std::string vertexShader;
	if (shaderFile.is_open()) {
		std::string line;
		while (std::getline(shaderFile, line)) {
			vertexShader += line;
			vertexShader += '\n';
		}
	}
	else {
		ErrorManager::error("failed to read file " + vertexShaderFilePath);
	}
	
	//compile shader
	const char* vertexShaderPtr = vertexShader.c_str();
	glShaderSource(_vertexShaderID, 1, &vertexShaderPtr, nullptr);
	glCompileShader(_vertexShaderID);
	//error checking
	GLint success = 0;
	glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<char> errorLogVec(maxLength);
		glGetShaderInfoLog(_vertexShaderID, maxLength, &maxLength, &errorLogVec[0]);
		std::string errorLog;
		for (char c : errorLogVec) {
			errorLog += c;
		}
		glDeleteShader(_vertexShaderID);
		ErrorManager::error("Failed to compile vertex shader, error log:\n" + errorLog);
	}
	//then fragment shader -- same as above
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!_vertexShaderID) {
		ErrorManager::error("Error in fragment shader creating");
	}
	std::ifstream shaderFile1(fragmentShaderFilePath);
	std::string fragmentShader;
	if (shaderFile.is_open()) {
		std::string line;
		while (std::getline(shaderFile1, line)) {
			fragmentShader += line;
			fragmentShader += '\n';
		}
	}
	else {
		ErrorManager::error("Failed to read file " + fragmentShaderFilePath);
	}
	const char* fragmentShaderPtr = fragmentShader.c_str();
	glShaderSource(_fragmentShaderID, 1, &fragmentShaderPtr, nullptr);
	glCompileShader(_fragmentShaderID);
	success = 0;
	glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(_fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLogVec(maxLength);
		glGetShaderInfoLog(_fragmentShaderID, maxLength, &maxLength, &errorLogVec[0]);
		std::string errorLog;
		for (char c : errorLogVec) {
			errorLog += c;
		}
		glDeleteShader(_fragmentShaderID);
		ErrorManager::error("Failed to compiled fragment shader, error log:\n" + errorLog);
	}
}

void GLSLProgram::linkShaders()
{
	//creating program and linking shaders to it
	_programID = glCreateProgram();
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glBindAttribLocation(_programID, 0, "vertexPosition");
	// Link our program
	glLinkProgram(_programID);

	// error checking
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLogVec(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLogVec[0]);
		std::string errorLog;
		for (char c : infoLogVec) {
			errorLog += c;
		}
		ErrorManager::error("error linking program , error log: " + errorLog);
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(_programID, uniformName.c_str());
}

GLint GLSLProgram::getUniformBlockIndex(const std::string& blockName)
{
	return glGetUniformBlockIndex(_programID, blockName.c_str());
}

GLuint GLSLProgram::getPID()
{
	return _programID;
}

#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	this->ID = LoadShaders(vertexPath, fragmentPath);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

int Shader::getUniformLocation(const std::string& name) const {
	return glGetUniformLocation(ID, name.c_str());
}

Shader::~Shader() {
	glDeleteProgram(ID);
}



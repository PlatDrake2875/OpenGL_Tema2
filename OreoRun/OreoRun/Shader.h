#pragma once
#include <string>
#include <GL/glew.h>
#include <loadShaders.h>

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	int getUniformLocation(const std::string& name) const;
	~Shader();
};


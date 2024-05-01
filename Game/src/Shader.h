#pragma once

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GE
{
	class Shader
	{
	public:
		unsigned int m_shaderID;

		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void use();
		void setUniformBool(const std::string& name, bool value) const;
		void setUniformInt(const std::string& name, int value) const;
		void setUniformFloat(const std::string& name, float value) const;
		void setUinforFloat2d(const std::string& name, float value, float value2) const;
		void setUinforMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		void checkCompileErrors(unsigned int shader, std::string type);
	};
}
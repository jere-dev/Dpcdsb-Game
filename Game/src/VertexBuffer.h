#pragma once

#include <GLAD/glad.h>

#include <vector>

namespace GE {

	class VertexBuffer 
	{
	public:

		VertexBuffer(std::vector<float>& vertices);
		~VertexBuffer();
		void AddAtribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		
		void Bind();
		void UnBind();


	private:
		unsigned int VertexBuffer_ID;
		
	};
}
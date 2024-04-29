#pragma once

#include <GLAD/glad.h>

#include <vector>

namespace GE {

	class VertexBuffer 
	{
	public:
		unsigned int VertexBuffer_ID;

		VertexBuffer(std::vector<float>& vertices);
		~VertexBuffer();
		void Bind();
		void UnBind();


	private:
		
	};
}
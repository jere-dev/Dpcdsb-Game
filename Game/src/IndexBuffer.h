#pragma once
#include "GLAD/glad.h"

#include <vector>

namespace GE {
	class IndexBuffer 
	{
	public:
		IndexBuffer(std::vector<unsigned int>& indices);
		~IndexBuffer();
		void Bind();
		void UnBind();

	private:
		unsigned int IndexBuffer_ID;
	};
}
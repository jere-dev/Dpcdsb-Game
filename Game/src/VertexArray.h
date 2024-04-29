#pragma once
#include <GLAD/glad.h>

namespace GE {

	class VertexArray
	{
	public:
		unsigned int VertexArray_ID;

		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();


	private:
	};
}
#include "VertexArray.h"

namespace GE {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &VertexArray_ID);
		this->Bind();
	}


	void VertexArray::Bind()
	{
		glBindVertexArray(VertexArray_ID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &VertexArray_ID);
	}

}
#include "IndexBuffer.h"

namespace GE {
	IndexBuffer::IndexBuffer(std::vector<unsigned int>& indices)
	{
		glGenBuffers(1, &IndexBuffer_ID);

		this->Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	}
	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer_ID);
	}
	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &IndexBuffer_ID);
	}
}
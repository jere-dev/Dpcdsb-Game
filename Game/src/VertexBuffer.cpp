#include "VertexBuffer.h"

namespace GE {
	VertexBuffer::VertexBuffer(std::vector<float>& vertices)
	{
		glGenBuffers(1, &VertexBuffer_ID);
		this->Bind();

		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}

	void VertexBuffer::AddAtribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer_ID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &VertexBuffer_ID);
	}
}
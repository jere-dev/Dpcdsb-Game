#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

int main()
{
	GE::Window win = GE::Window(450, 800, "Sky");

	GE::Shader shader = GE::Shader("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/shader.vs", 
		"C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/shader.fs");
	shader.use();

	std::vector<float> vertices{
	 1.0f,  1.0f, 0.0f,  // top right
	 1.0f, -1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f,  // bottom left
	-1.0f,  1.0f, 0.0f   // top left 
	};

	std::vector<unsigned int> indices{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	GE::VertexArray VAO = GE::VertexArray();
	GE::VertexBuffer VBO = GE::VertexBuffer(vertices);
	GE::IndexBuffer IBO = GE::IndexBuffer(indices);

	VBO.UnBind();
    VAO.Unbind();
	IBO.UnBind(); // order matters

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.setUinforFloat2d("iResolution", 450, 800);

	float time = 0;
	shader.setUniformFloat("iTime", time);

	//render after clear and before update or blank screen
	while (!glfwWindowShouldClose(win.m_window))
	{
		//float currentFrame = glfwGetTime();
		time = glfwGetTime();
		shader.setUniformFloat("iTime", time);
		win.clear();

		shader.use();
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		win.update();
	}

}
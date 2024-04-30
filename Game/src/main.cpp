#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

int main()
{
	GE::Window win = GE::Window(600, 800, "Sky");

	GE::Shader shader = GE::Shader("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/texture-shader.vs", 
		"C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/texmix-shader.fs");
	shader.use();

	stbi_set_flip_vertically_on_load(true);

	std::vector<float> vertices{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	std::vector<unsigned int> indices{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	GE::VertexArray VAO = GE::VertexArray();
	GE::VertexBuffer VBO = GE::VertexBuffer(vertices);
	GE::IndexBuffer IBO = GE::IndexBuffer(indices);

	VBO.AddAtribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // this might cause problems?
	VBO.AddAtribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VBO.AddAtribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VBO.UnBind();
    VAO.Unbind();
	IBO.UnBind(); // order matters

	GE::Texture texture = GE::Texture("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/textures/container.jpg", GL_RGB);
	texture.Bind(GL_TEXTURE0);

	GE::Texture texture2 = GE::Texture("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/textures/awesomeface.png", GL_RGBA);
	texture2.Bind(GL_TEXTURE1);

	shader.setUniformInt("texture1", 0);
	shader.setUniformInt("texture2", 1);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.setUinforFloat2d("iResolution", 600, 800);

	float time = 0;
	shader.setUniformFloat("iTime", time);

	//render after clear and before update or blank screen
	while (!glfwWindowShouldClose(win.m_window))
	{
		//float currentFrame = glfwGetTime();
		time = glfwGetTime();
		shader.setUniformFloat("iTime", time);
		win.clear();

		texture.Bind(GL_TEXTURE0);
		texture2.Bind(GL_TEXTURE1);

		shader.use();
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		win.update();
	}

}
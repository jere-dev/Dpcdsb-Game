#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "camera.h"

std::map<int, bool> keymap;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keymap[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keymap[key] = false;
	}
}


static bool KeyPressed(int key)
{
	if (keymap.find(key) != keymap.end())
	{
		return keymap[key];
	}
	else
	{
		return false;
	}
}

int main()
{
	GE::Window win = GE::Window(600, 800, "Sky", key_callback);
	GE::Camera cam = GE::Camera(-.6, .6, -.8, .8);
	//cam.SetPosition({0.5f, 0.5f, 0.0f});
	//cam.SetRotation(90.0f);

	GE::Shader shader = GE::Shader("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/cam-shader.vs", 
		"C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/texture-shader.fs");
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

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());

	shader.setUinforFloat2d("iResolution", 600, 800);

	float time = 0;
	shader.setUniformFloat("iTime", time);

	//render after clear and before update or blank screen
	while (!glfwWindowShouldClose(win.m_window))
	{
		
		if (KeyPressed(GLFW_KEY_A))
		{
			auto tempvec = cam.GetPosition();
			tempvec.x += .001;
			cam.SetPosition(tempvec);
			shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());
		}

		if (KeyPressed(GLFW_KEY_D))
		{
			auto tempvec = cam.GetPosition();
			tempvec.x -= .001;
			cam.SetPosition(tempvec);
			shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());
		}
		if (KeyPressed(GLFW_KEY_S))
		{
			auto tempvec = cam.GetPosition();
			tempvec.y += .001;
			cam.SetPosition(tempvec);
			shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());
		}
		if (KeyPressed(GLFW_KEY_W))
		{
			auto tempvec = cam.GetPosition();
			tempvec.y -= .001;
			cam.SetPosition(tempvec);
			shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());
		}

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
#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "camera.h"

#include "components.h"

#include <glm/gtc/matrix_transform.hpp>
#include <flecs.h>
#include <box2d/box2d.h>

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

glm::mat4 GetModelMatrix(GE::Com::transform t)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position);
	transform = glm::scale(transform, t.scale);
	transform = glm::rotate(transform, glm::radians(t.Rotation), glm::vec3(0, 0, 1));
	glm::mat4 modelMatrix = glm::inverse(transform);

	return modelMatrix;
}



int main()
{
	flecs::world world;
	b2World boxWorld({ 0.0f, -9.8f });
	

	glm::vec3 gscale = { 10.0f, 10.0f, 1.0f };

	auto player = world.entity("player")
		.set<GE::Com::transform>({ {0.0f, -1.0f, 0.0f}, gscale, 0.0f })
		.set<GE::Com::texture>({ 8.0f, 14.0f })
		.add<GE::Com::player>();

		world.entity()
		.set<GE::Com::transform>({ {0.0f, 0.0f, 0.0f}, gscale, 0.0f })
		.set<GE::Com::texture>({3.0f, 12.0f})
		.add<GE::Com::platform>();

		world.entity()
		.set<GE::Com::transform>({ {-0.72f, 0.0f, 0.0f}, gscale, 0.0f })
		.set<GE::Com::texture>({ 3.0f, 12.0f })
		.add<GE::Com::platform>();



	GE::Window win = GE::Window(600, 960, "Sky", key_callback);
	GE::Camera cam = GE::Camera(-1.6, 1.6, -1.0, 1.0);
	//cam.SetPosition({0.5f, 0.5f, 0.0f});
	//cam.SetRotation(90.0f);

	GE::Shader shader = GE::Shader("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/cam-shader.vs", 
								   "C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/shaders/texture-shader.fs");


	shader.use();

	stbi_set_flip_vertically_on_load(true);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	GE::Texture texture = GE::Texture("C:/Users/jerem/Desktop/Dpcdsb-Game/Game/assets/tilemap/tilemap2.png", GL_RGBA);
	shader.setUinforFloat2d("spriteSheetSize", texture.getWidth(), texture.getHeight());
	shader.setUinforFloat2d("spriteSize", 25.0f, 25.0f);
	shader.setUinforFloat2d("tcxy", 3.0f, 12.0f);
	//texture.Bind(GL_TEXTURE0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix());

	float time = 0;
	shader.setUniformFloat("iTime", time);

	//render after clear and before update or blank screen
	while (!glfwWindowShouldClose(win.m_window))
	{

		world.each([&](GE::Com::player player, GE::Com::transform& t) { 
			if (KeyPressed(GLFW_KEY_A))
			{
				t.Position.x += .001;
			}
			if (KeyPressed(GLFW_KEY_D))
			{
				t.Position.x -= .001;
			}

			if (KeyPressed(GLFW_KEY_S))
			{
				t.Position.y += .001;
			}

			if (KeyPressed(GLFW_KEY_W))
			{
				t.Position.y -= .001;
			}
		});

		time = glfwGetTime();
		shader.setUniformFloat("iTime", time);
		win.clear();

		world.each([&](GE::Com::texture tc, GE::Com::transform t) { // flecs::entity argument is optional
			shader.setUinforMat4("ViewProjection", cam.GetViewProjectionMatrix() * GetModelMatrix(t));
			shader.setUinforFloat2d("tcxy", tc.texX, tc.texY);
			shader.use();
			VAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		});


		win.update();
	}

}
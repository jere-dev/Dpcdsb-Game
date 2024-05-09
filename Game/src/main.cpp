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

void addPlatform(flecs::world& world, glm::vec3 gscale, int x, int y)
{
	
	world.entity()
		.set<GE::Com::transform>({ {x*-0.72f, y*-0.72f, 0.0f}, gscale, 0.0f })
		.set<GE::Com::texture>({ 5.0f, 12.0f })
		.add<GE::Com::rigidBody>()
		.add<GE::Com::platform>();
}

int main()
{

	flecs::world world;
	b2Vec2 gravity = { 0.0f, -60.0f };
	b2World boxWorld(gravity);

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	glm::vec3 gscale = { 5.0f, 5.0f, 1.0f };

	auto player = world.entity("player")
		.set<GE::Com::transform>({ {0.0f, -1.0f, 0.0f}, gscale, 0.0f })
		.set<GE::Com::texture>({ 8.0f, 14.0f })
		.add<GE::Com::rigidBody>()
		.add<GE::Com::player>();

	for (int i = 0; i < 5; i++) {
		addPlatform(world, gscale, i, 0);
	}

	for (int i = 0; i < 5; i++) {
		addPlatform(world, gscale, 5+i, 1);
	}
	for (int i = 0; i < 5; i++) {
		addPlatform(world, gscale, 10+i, 3);
	}


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



	world.each([&](GE::Com::rigidBody& rb, GE::Com::transform& t, GE::Com::platform p) {
		int width, height;
		glfwGetWindowSize(win.m_window, &width, &height);
		
		float posX, posY;
		posX = (t.Position.x * width * (-1))-475;
		posY = (t.Position.y * height * (-1));

		rb.bodyDef.position.Set(posX, posY);

		rb.body = boxWorld.CreateBody(&rb.bodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(400.0f, 100.0f);

		rb.body->CreateFixture(&groundBox, 0.0f);
	});

	world.each([&](GE::Com::rigidBody& rb, GE::Com::transform& t, GE::Com::player p) {
		int width, height;
		glfwGetWindowSize(win.m_window, &width, &height);

		float posX, posY;
		posX = t.Position.x * width * (-1);
		posY = t.Position.y * height * (-1);

		rb.bodyDef.type = b2_dynamicBody;
		rb.bodyDef.position.Set(posX, posY);
		rb.body = boxWorld.CreateBody(&rb.bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(0.5f, 0.5f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		rb.body->CreateFixture(&fixtureDef);
	});

	


	float cMovespeed = 0.0005;
	float pt = glfwGetTime();
	//render after clear and before update or blank screen
	while (!glfwWindowShouldClose(win.m_window))
	{
		float t = glfwGetTime();
		if (t>= pt+.3)
		{
			pt = t;
			if (KeyPressed(GLFW_KEY_A) || KeyPressed(GLFW_KEY_D))
			{
					world.each([&](GE::Com::player player, GE::Com::texture& tex) {
						if (tex.texX == 8)
						{
							tex.texX = 9;
						}
						else
						{
							tex.texX = 8;
						}

						});
				

			}
			else
			{
				world.each([&](GE::Com::player player, GE::Com::texture& tex) {
					tex.texX = 8;
					});
			}
		}
		world.each([&](GE::Com::player player, GE::Com::rigidBody rb, GE::Com::transform& t, GE::Com::texture tex) {
			boxWorld.Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = rb.body->GetPosition();

			int width, height;
			glfwGetWindowSize(win.m_window, &width, &height);

			float posX, posY;
			t.Position.x = ((position.x+550) / width) * (-1);
			t.Position.y = ((position.y+550) / height) * (-1);

			printf("%4.2f %4.2f\n", rb.body->GetLinearVelocity().x, rb.body->GetLinearVelocity().y);
		});

		world.each([&](GE::Com::player player, GE::Com::rigidBody rb) { 
			b2Vec2 vel = b2Vec2(gravity.x, gravity.y);

			if (KeyPressed(GLFW_KEY_A))
			{
				vel.x = -200.0f;
				glm::vec3 cpos = cam.GetPosition();
				cpos.x -= cMovespeed;
				cam.SetPosition(cpos);
			}
			if (KeyPressed(GLFW_KEY_D))
			{
				vel.x = 200.0f;
				glm::vec3 cpos = cam.GetPosition();
				cpos.x += cMovespeed;
				cam.SetPosition(cpos);
			}

			if (KeyPressed(GLFW_KEY_S))
			{
				vel.y = -200;
				glm::vec3 cpos = cam.GetPosition();
				cpos.y -= cMovespeed;
				cam.SetPosition(cpos);
			}

			if (KeyPressed(GLFW_KEY_W))
			{
				vel.y = 500;
				glm::vec3 cpos = cam.GetPosition();
				cpos.y += cMovespeed;
				cam.SetPosition(cpos);
			}

			rb.body->SetLinearVelocity(vel);
			rb.body->SetSleepingAllowed(false);
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
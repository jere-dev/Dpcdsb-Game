#pragma once
#include "glm/glm.hpp"
#include "box2d/box2d.h"

namespace GE {

	namespace Com {
		struct transform
		{
			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			glm::vec3 scale = {0.5f, 0.5f, 1.0f};
			float Rotation = 0.0f;
		};

		struct player
		{};

		struct platform
		{};

		struct texture
		{
			float texX, texY;
		};

		struct rigidBody
		{
			b2BodyDef bodyDef;
		};
	}
}
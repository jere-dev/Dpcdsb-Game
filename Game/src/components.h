#pragma once
#include "glm/glm.hpp"

namespace GE {

	namespace Com {
		struct transform
		{
			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			float Rotation = 0.0f;
		};

		struct player
		{};

		struct platform
		{};
	}
}
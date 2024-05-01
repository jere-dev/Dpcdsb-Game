#include "camera.h"

namespace GE {
	Camera::Camera(float left, float right, float bottom, float top)
		:ProjectionMatrix(glm::ortho(left, right, bottom, top)), ViewMatrix(1.0f)// bot top -1 1
	{
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void Camera::ReCalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position);
		transform = glm::rotate(transform, glm::radians(Rotation), glm::vec3(0, 0, 1));

		ViewMatrix = glm::inverse(transform);
		ViewProjectionMatrix = ProjectionMatrix* ViewMatrix;
	}


}
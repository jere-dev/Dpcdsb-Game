#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GE {

	class Camera
	{
	public:
		Camera(float left, float right, float top, float bottom);

		const glm::vec3& GetPosition() const { return Position; }
		void SetPosition(const glm::vec3& pos) { Position = pos; ReCalculateViewMatrix(); }

		float GetRotation() const { return Rotation; }
		void SetRotation(float rot) { Rotation = rot; ReCalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

	private:
		void ReCalculateViewMatrix();

	private:
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;

		glm::vec3 Position = {0.0f, 0.0f, 0.0f};
		float Rotation = 0.0f;
	};
}
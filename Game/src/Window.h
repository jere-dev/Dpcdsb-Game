#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace GE {

	class Window
	{
	public:
		Window(int hieght, int width, const char* title);
		~Window();
		void clear();
		void update();

		GLFWwindow* m_window;

	private:
		int m_hieght, m_width;
		const char* m_title;
	};
}
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static class {
public:
	const char* title = "Sample 01";
	int width = 800;
	int height = 600;
} window_context;

int main()
{
	GLFWwindow* window = nullptr;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(window_context.width, window_context.height,
							  window_context.title, nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	glClearColor(0, 0, 0.3f, 0);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

static const unsigned int getWindowDimension(bool is_height) {
	int dimension;
	string input;
	while (true) {
		try {
			cout << "Input the desired window " << (is_height ? "height" : "width") << " [>= 0]: ";
			cin >> input;

			dimension = stoi(input);
			if (dimension <= 0) {
				continue;
			}

			break;
		}
		catch (const exception& e) {
			continue;
		}
	}

	return dimension;
}

static const string getWindowTitle() {
	string title;

	cout << "Input the desired window title: ";
	cin >> title;

	return title;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void processWindowInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void) {
	const int width = getWindowDimension(false), height = getWindowDimension(true);
	const string title = getWindowTitle();

	if (!glfwInit()) {
		cerr << "Failed to initialise GLFW." << endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window) {
		cerr << "Failed to create a GLFW window." << endl;
		glfwTerminate();
		return 2;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialise GLEW." << endl;
		return 3;
	}

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	while (!glfwWindowShouldClose(window)) {
		processWindowInput(window);

		glClearColor(.0f, 1.f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
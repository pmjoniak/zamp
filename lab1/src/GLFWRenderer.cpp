#include <cmath>
#include <thread>
#include "GLFWRenderer.h"
#include <iostream>


using namespace std;

GLFWRenderer::GLFWRenderer(int w, int h) : width{ w }, height{ h }
{
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(w, h, glfwGetVersionString(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
}

GLFWRenderer::~GLFWRenderer()
{
	glfwMakeContextCurrent(window);
	glfwDestroyWindow(window);
}

bool GLFWRenderer::isRunning()
{
	return glfwWindowShouldClose(window);
}

void GLFWRenderer::sleepUntilNextFrame(int frame_count)
{
	next_frame += frame_count * frame_duration(1);
	this_thread::sleep_until(next_frame);
}

void mouse_cb(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		printf("Click!\n");
}

void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
			return;
		}
		printf("Stroke!\n");
	}
}

void GLFWRenderer::run()
{
	glfwSetKeyCallback(window, key_cb);
	glfwSetMouseButtonCallback(window, mouse_cb);

	while (!glfwWindowShouldClose(window))
	{
		glfwMakeContextCurrent(window);

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// glFrustum(fNear *(-fFov * ratio + headX),
		// 		  fNear *(fFov * ratio + headX),
		// 		  fNear *(-fFov + headY),
		// 		  fNear *(fFov + headY),
		// 		  fNear, fFar);
		glOrtho(0, width, 0, height, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_TEXTURE_2D);
		glColor3f(1, 0, 0);
		glPointSize(20);
		glBegin(GL_POINTS);
		glVertex2f(200, 200);
		glEnd();
		drawGrid(4, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
		sleepUntilNextFrame(15);
	}
}

void GLFWRenderer::drawGrid(int xdiv, int ydiv)
{
	float xres = width / xdiv;
	float yres = height / ydiv;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 1; i < xdiv; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(i * xres, 0);
		glVertex2f(i * xres, height);
		glEnd();
	}
	for (int i = 1; i < ydiv; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(0, i * yres);
		glVertex2f(width, i * yres);
		glEnd();
	}
}

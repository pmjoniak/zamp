#pragma once
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWRenderer
{
private:
	GLFWwindow *window;
	int width;
	int height;

private:
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::duration<int64_t, std::ratio<1, 6000000>> clock_resolution;
	typedef std::chrono::steady_clock::duration frame_duration;
	clock::time_point next_frame = clock::now();

public:
	GLFWRenderer(int width, int height);
	~GLFWRenderer();

	void run();
	bool isRunning();

	void sleepUntilNextFrame(int frame_count = 1);

	void drawGrid(int xdiv, int ydiv);

};

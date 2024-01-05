#pragma once
#include "libraries.h"
#include "Executable.h"
#include "Chrono.h"

class Window
{
public:
	Window() = default;
	~Window() = default;
	void Run();

private:
	int singleThreadTime = 0;
	int multiThreadTime = 0;
	int multiThreadTimeCoroutine = 0;

	GLFWwindow *window = nullptr;
	ImGuiIO *io;
    Executable executable;
    Chrono chrono;

	int Setup();
	void MainLoop();
	void Shutdown();
	void OnButtonClick();
};
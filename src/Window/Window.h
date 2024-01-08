#pragma once
#include "../libraries.h"
#include "../Chrono/Chrono.h"
#include "../Thread/SingleThread.cpp"
#include "../Thread/MultiThread.cpp"
#include "../Thread/CoroutineThread.cpp"
#include "../Executable/Executable.h"

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

	int iteration = 10;

	GLFWwindow *window = nullptr;
	ImGuiIO *io = nullptr;

	int Setup();
	void MainLoop();
	void Shutdown();
	void OnButtonClick();
};

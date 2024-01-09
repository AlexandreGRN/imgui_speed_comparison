#pragma once

#include "../libraries.hpp"
#include "../Chrono/Chrono.hpp"
#include "../Thread/SingleThread.hpp"
#include "../Thread/MultiThread.hpp"
#include "../Thread/CoroutineThread.hpp"
#include "../Executable/Executable.hpp"

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

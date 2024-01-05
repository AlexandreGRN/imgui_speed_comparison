#include "imgui.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include "opengl_shader.h"
#include "file_manager.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <bits/stdc++.h> 
#include <boost/coroutine2/all.hpp>

class Chrono 
{
public:
    Chrono() = default;
    ~Chrono() = default;
    inline void start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
    inline void stop()
    {
        m_end = std::chrono::high_resolution_clock::now();
    }
    inline void print_duration(std::string message = "")
    {
        std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() << " microsec\n";
    }
    inline std::chrono::milliseconds stop_print_return_duration(std::string message = "")
    {
        stop();
        print_duration(message);
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start);
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};

class Executable
{
public:
    Executable() = default;
    ~Executable() = default;
    void long_function();
    void long_function_repeat_singleThread()
    {
        for (int i = 0; i < 10; i++)
            long_function();
    }
    void long_function_repeat_multiThread()
    {
        std::vector<std::jthread> threads;

        for (int i = 0; i < 10; i++)
            threads.push_back(std::jthread(&Executable::long_function, this));
    }
    
	void coroutineProcess()
	{
		boost::coroutines2::coroutine<void>::pull_type coro([&](boost::coroutines2::coroutine<void>::push_type& yield)
		{
        	for (int i = 0; i < 10; ++i) {
				long_function();
				yield();
			}
    	});

		while (coro) {
			coro();
		}
	}
};

void Executable::long_function()
{
    std::vector<int> v;
    for (int i = 0; i < 10000; i++)
    {
        v.push_back(i);
        std::sort(v.begin(), v.end());
    }
}

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}




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

void Window::OnButtonClick()
{
	// Single Thread
    chrono.start();
    executable.long_function_repeat_singleThread();
    auto duration1 = chrono.stop_print_return_duration("Single Threa: ");

    // Multi Thread
    chrono.start();
    executable.long_function_repeat_multiThread();
    auto duration2 = chrono.stop_print_return_duration("Multi Thread: ");
    
    // Multi Thread with coroutine
    chrono.start();
	executable.coroutineProcess();
	auto duration3 = chrono.stop_print_return_duration("Multi Thread with coroutine: ");
	
	singleThreadTime += duration1.count();
	multiThreadTime += duration2.count();
	multiThreadTimeCoroutine += duration3.count();
}

int Window::Setup()
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();



	return 0;
}

void Window::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Main window style
		glfwPollEvents();
		glClearColor(1.00f, 0.00f, 0.00f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		// fSstart new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		ImGui::Begin("Comparison graph");
		if (ImGui::Button("Click me!"))
		{
			OnButtonClick();
		}
		 ImGui::Text("Single Thread Time: %d", singleThreadTime);
		 ImGui::Text("Multi Thread Time: %d", multiThreadTime);
		 ImGui::Text("Multi Thread Time Coroutine: %d", multiThreadTimeCoroutine);

        ImGui::End();

    ImGui::End(); // End of the "Text Box Example" window

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glfwSwapBuffers(window);
	}
}

void Window::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Run()
{
	Setup();
	MainLoop();
	Shutdown();
}

int main(int, char **)
{
	Window window;
	window.Run();

	return 0;
}

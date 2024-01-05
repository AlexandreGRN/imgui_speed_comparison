#include "Window.h"

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


void Window::OnButtonClick()
{
	// Single Thread
    chrono.start();
    executable.long_function_repeat_singleThread();
    auto duration1 = chrono.stop();

    // Multi Thread
    chrono.start();
    executable.long_function_repeat_multiThread();
    auto duration2 = chrono.stop();
    
    // Multi Thread with coroutine
    chrono.start();
	executable.long_function_repeat_coroutine();
	auto duration3 = chrono.stop();
	
	multiThreadTime = duration2.count();
	multiThreadTimeCoroutine = duration3.count();
	singleThreadTime = duration1.count();
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
		 if (ImGui::Button("Start comparison"))
		 {
		 	OnButtonClick();
		 }
		 ImGui::Text("Single Thread Time: %d", singleThreadTime);
		 ImGui::Text("Multi Thread Time: %d", multiThreadTime);
		 ImGui::Text("Multi Thread Time Coroutine: %d", multiThreadTimeCoroutine);

        ImGui::End();

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

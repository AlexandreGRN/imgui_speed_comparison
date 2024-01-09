#include "Window.hpp"

void Window::OnButtonClick()
{
	Chrono::Chrono chrono;
	Executable::Executable executable{iteration};

	singleThreadTime = chrono.runFunction<Thread::SingleThread, Executable::Executable>(&Executable::Executable::action, &executable);
	multiThreadTime = chrono.runFunction<Thread::MultiThread, Executable::Executable>(&Executable::Executable::action, &executable);
	multiThreadTimeCoroutine = chrono.runFunction<Thread::CoroutineThread, Executable::Executable>(&Executable::Executable::action, &executable);
}

int Window::Setup()
{
	// Setup window
	glfwSetErrorCallback([](int error, const char *description){});
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
	ImPlot::CreateContext();
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
		 ImGui::Text("Number of iterations of the function");
		 ImGui::SliderInt("", &iteration, 1, 2000);
		  if (ImGui::Button("Start comparison"))
		  {
		 	OnButtonClick();
		  }
		 ImGui::Text("Single Thread Time: %d milliseconds", singleThreadTime);
		 ImGui::Text("Multi Thread Time: %d milliseconds", multiThreadTime);
		 ImGui::Text("Multi Thread Time Coroutine: %d milliseconds", multiThreadTimeCoroutine);

        ImGui::End();

		/*ImGui::Begin("Comparison graph");
		ImPlot::SetNextPlotLimits(0, 2000, 0, 1000);
		if (ImPlot::BeginPlot("Comparison graph", "Number of iterations", "Time in milliseconds", ImVec2(-1, -1), ImPlotFlags_NoChild))
		{
			ImPlot::PlotLine("Single Thread", &iteration, &singleThreadTime, 2000);
			ImPlot::PlotLine("Multi Thread", &iteration, &multiThreadTime, 2000);
			ImPlot::PlotLine("Multi Thread Coroutine", &iteration, &multiThreadTimeCoroutine, 2000);
			ImPlot::EndPlot();
		}
		ImGui::End();*/

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
	ImPlot::DestroyContext();
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

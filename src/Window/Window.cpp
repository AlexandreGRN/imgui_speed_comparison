#include "Window.hpp"


// Function to run the comparison depending on the number of iterations chosen in the UI
void Window::OnButtonClick()
{
	Chronos::Chrono chrono;
	Launchers::ExecutableLauncher launcher;
	Executables::Executable executable{iteration};

	singleThreadTime = launcher.runFunction<Threads::SingleThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
	multiThreadTime = launcher.runFunction<Threads::MultiThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
	multiThreadTimeCoroutine = launcher.runFunction<Threads::CoroutineThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
}

// Function to run the comparison for the graph before the start of the app
void Window::SetupGraph()
{
	Chronos::Chrono chrono;
	Launchers::ExecutableLauncher launcher;
	Executables::Executable executable{0};

	for (int i = 0 ; i < 5 ; i++)
	{
		executable.setIteration(iterationArray[i]);
		singleThreadTimeResults[i] = launcher.runFunction<Threads::SingleThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
		multiThreadTimeResults[i] = launcher.runFunction<Threads::MultiThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
		multiThreadTimeCoroutineResults[i] = launcher.runFunction<Threads::CoroutineThread, Executables::Executable, Chronos::Chrono>(&Executables::Executable::action, &executable, chrono);
	}
}

// Function to setup the window
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

// Function to run the main loop of the app and render the UI
void Window::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Main window style
		glfwPollEvents();
		glClearColor(1.00f, 0.00f, 0.00f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Window 1
		ImGui::Begin("Comparison specific value");
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

		// Window 2
		ImGui::Begin("Comparison graph per iteration");
		 ImPlot::SetNextPlotLimits(0, 1200, 0, 300);
		 if (ImPlot::BeginPlot("Comparison graph", "Number of iterations", "Time in milliseconds", ImVec2(-1, -1), ImPlotFlags_NoChild))
		 {
			ImPlot::PlotLine("Single Thread", iterationArray, singleThreadTimeResults, 5);
			ImPlot::PlotLine("Multi Thread", iterationArray, multiThreadTimeResults, 5);
			ImPlot::PlotLine("Multi Thread Coroutine", iterationArray, multiThreadTimeCoroutineResults, 5);
			ImPlot::EndPlot();
		 }
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

// Function to shutdown the window
void Window::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Function to setup the app, run it and shutdown it at the end
void Window::Run()
{
	SetupGraph();
	Setup();
	MainLoop();
	Shutdown();
}

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

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void OnButtonClick(int& singleThreadTime, int& multiThreadTime, int& multiThreadTimeCoroutine)
{
	singleThreadTime += 1;
	multiThreadTime += 2;
	multiThreadTimeCoroutine += 3;
}

int main(int, char **)
{
	int singleThreadTime = 0;
	int multiThreadTime = 0;
	int multiThreadTimeCoroutine = 0;

	// Setup window //
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
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
	ImGuiIO &io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

    // Main loop
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
			OnButtonClick(singleThreadTime, multiThreadTime, multiThreadTimeCoroutine);
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

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

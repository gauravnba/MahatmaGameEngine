/** Sample class created to check if Window is generated using OpenGL.*/

#include "pch.h"

#include <stdio.h>
#include <windows.h>
#include "SList.h"
#include "GLFW/glfw3.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* sampleWindow;
	sampleWindow = glfwCreateWindow(1280, 720, "Sample Window", NULL, NULL);

	if (sampleWindow == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(sampleWindow, GLFW_STICKY_KEYS, GL_TRUE);

	// Check if the ESC key was pressed or the window was closed
	while ((glfwGetKey(sampleWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS) && !glfwWindowShouldClose(sampleWindow))
	{
		glfwSwapBuffers(sampleWindow);
		glfwPollEvents();
	}

	// SList created on the stack to check dependency on Library.Desktop
	MahatmaGameEngine::SList(10);

    return 0;
}
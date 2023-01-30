#ifndef INTERNALFUNC_H
#define INTERNALFUNC_H
//Dear imGui interface headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Shader.h"
#include <iostream>

//constants
int winHeight = 625;
int winWidth = 875;
GLuint VBO, VAO;
const char* GAMENAME = "Mirage Source";
int running = 1;
//window accessor :: indentifies so we can create window
GLFWwindow* window;
bool drawTriangle;

//functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void initOGL();
void display();
void renderScene();
void draw();
void clearBuff();
void destroyWin();
void initMenu();
void MMenu();

void initMenu()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16);
	style.Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
};
void MainMenu()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
		MMenu();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

void MMenu()
{
		ImGui::Begin("test", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		ImGui::BeginChild("##LeftSide", ImVec2(200, ImGui::GetContentRegionAvail().y));
		{
			ImGui::Text("Testme");
			ImGui::Checkbox("Draw Triangle", &drawTriangle);
		}
		ImGui::EndChild();
		ImGui::End();
}

//closes app to free memory
void destroyWin()
{
	glfwDestroyWindow(window);
	glfwTerminate();
};

//clears buffer
void clearBuff()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
};

enum class Menu
{
	m_Menu,
	m_Login,
	m_Create,
};
//establishes shaders
void draw()
{
	Shader ourShader("shader.vs", "shader.fs");
	//render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	MainMenu();

	ourShader.use();
	glBindVertexArray(VAO);

	if (drawTriangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);


	//glfw swa[ buffer/poll IO events
	glfwSwapBuffers(window);
	glfwPollEvents();

	//renders output
	renderScene();
};

//renders objects
void renderScene()
{
	float vertices[] =
	{
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//bid vertex array oject
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(VAO);
};

void initOGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
};

void display()
{
	window = glfwCreateWindow(winWidth, winHeight, GAMENAME, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad load all opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
};

#endif
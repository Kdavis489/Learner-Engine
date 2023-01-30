//Kazmos Source
#include "includes.h"

int main()
{
	initOGL();
	display();
	initMenu();

	if (running) //if running, glfw window should not close
	{
		//render loop ::will be moved to void display
		while (!glfwWindowShouldClose(window))
		{
			//input key processes
			processInput(window);

			//render
			draw();
		}
	}
	else
	{
		clearBuff();
		if (!running) //if not running GLFW should close window(s) to free allocated memory
		{
			if (glfwWindowShouldClose(window))
			{
				destroyWin();
			}
		}
	}
	return 0;
}
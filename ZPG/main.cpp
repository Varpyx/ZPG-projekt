/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author ...
 **/

#include "Application.h"

int main(void)
{
	Application app;
	app.initialization();	// OpenGL inicialization
	app.createScene();
	app.run();				// Rendering

	return 0;
}

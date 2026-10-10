/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Michal Poncza
 **/

#include "Application.h"

int main(void)
{
	Application app;
	app.initialization();	// OpenGL inicialization
	app.createScenes();
	app.run();				// Rendering

	return 0;
}

#pragma once

#ifdef BS_PLATFORM_WINDOWS

#include <application/application.h>
#include <logging/log.h>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

extern bs::Application* getApplication();

int main(int argc, char* args[]) {

	bs::Log::init();

	/* init sdl */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		BS_CORE_ERROR("SDL initialization failed. SDL Error: ", SDL_GetError());
		return -1;
	} else {
		BS_CORE_TRACE("SDL initialization succeeded.");
	}

	auto app = getApplication();
	
	/*init() needs to create an opengl-context! */
	app->init();

	/* init glew */
	if (glewInit() != GLEW_OK) {
		BS_CORE_ERROR("GLEW initialization failed.");
		return -1;
	} else {
		BS_CORE_TRACE("GLEW initialization succeeded.");
	}

	/* gameloop */
	app->run();

	SDL_Quit();
	delete app;
	
	return 0;

}
#endif // BS_PLATFORM_WINDOWS

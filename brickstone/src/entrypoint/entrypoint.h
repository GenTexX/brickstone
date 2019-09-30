#pragma once

#ifdef BS_PLATFORM_WINDOWS

#include <application/application.h>
#include <logging/log.h>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

extern bs::Application* getApplication();

int main(int argc, char* args[]) {

	spdlog::set_level(spdlog::level::trace);

	/* init sdl */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		bs::Log::error("SDL initialization failed. SDL Error: ", SDL_GetError());
		return -1;
	} else {
		bs::Log::info("SDL initialization succeeded.");
	}

	auto app = getApplication();
	
	app->init();

	/* init glew */
	if (glewInit() != GLEW_OK) {
		bs::Log::error("GLEW initialization failed.");
		return -1;
	} else {
		bs::Log::info("GLEW initialization succeeded.");
	}

	app->run();

	SDL_Quit();
	delete app;
	
	return 0;

}
#endif // BS_PLATFORM_WINDOWS

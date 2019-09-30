#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "keycode.h"

typedef void(*callback_function)(void);

namespace bs {

	class Window {

	private:
		SDL_GLContext m_glContext;
		SDL_Window* m_window;
		int m_width, m_height;
		int m_posX, m_posY;
		std::string m_title;
		uint64_t m_keystate;
		uint8_t m_mousebuttonstate;
		int mousePosX, mousePosY, mouseWheelDirection;



		callback_function resized = nullptr;
		callback_function moved = nullptr;
		callback_function minimized = nullptr;
		callback_function maximized = nullptr;
		callback_function hidden = nullptr;
		callback_function exposed = nullptr;
		callback_function entered = nullptr;
		callback_function left = nullptr;
		callback_function mousebuttondown = nullptr;
		callback_function mousebuttonup = nullptr;
		callback_function mousemotion = nullptr;
		callback_function mousewheel = nullptr;
		callback_function keydown = nullptr;
		callback_function keyup = nullptr;

		static int handleEvent(void* data, SDL_Event* event);

		void onWindowResize();
		void onWindowMove();
		void onWindowMaximize();
		void onWindowMinimize();
		void onWindowHide();
		void onWindowExpose();
		void onWindowEnter();
		void onWindowLeave();
		void onMouseButtonDown(SDL_MouseButtonEvent mousecode);
		void onMouseButtonUp(SDL_MouseButtonEvent mousecode);
		void onMouseMotion(SDL_MouseMotionEvent mousecode);
		void onMouseWheel(SDL_MouseWheelEvent mousecode);
		void onKeyDown(SDL_Scancode scancode);
		void onKeyUp(SDL_Scancode scancode);

		static KeyCode getKeyCode(SDL_Scancode scancode);
		static MouseCode getMouseCode(SDL_MouseButtonEvent mousecode);



	public:
		static SDL_Event event;
		Window(const int& width = 1024,
			const int& height = 768,
			const char* title = "BrickStone",
			const int& x = SDL_WINDOWPOS_CENTERED,				//WindowCentered
			const int& y = SDL_WINDOWPOS_CENTERED,				//WindowCentered
			Uint32 flags = 0);
		~Window();

		void update();
		bool shouldClose();

		void setWindowResizeCallback(callback_function resize);
		void setWindowMoveCallback(callback_function move);
		void setWindowMaximizeCallback(callback_function maximize);
		void setWindowMinimizeCallback(callback_function minimize);
		void setWindowHideCallback(callback_function hide);
		void setWindowExposeCallback(callback_function expose);
		void setWindowEnterCallback(callback_function enter);
		void setWindowLeaveCallback(callback_function leave);
		void setMouseButtonDownCallback(callback_function mousebuttondown);
		void setMouseButtonUpCallback(callback_function mousebuttonup);
		void setMouseMotionCallback(callback_function mousemotion);
		void setMouseWheelCallback(callback_function mousewheel);
		void setKeyDownCallback(callback_function keydown);
		void setKeyUpCallback(callback_function keyup);

		int getWidth();
		int getHeight();
		int getMaxWidth();
		int getMaxHeight();
		float getOpacity();
		int getXpos();
		int getYpos();
		std::string getTitle();

		void setWidth(const int& w);
		void setHeight(const int& h);
		void setMaxWidth(const int& w);
		void setMaxHeight(const int& h);
		void setOpacity(const float& o);
		void setXpos(const int& x);
		void setYpos(const int& y);
		void setTitle(const std::string& title);

	};

}
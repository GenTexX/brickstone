#include <bspch.h>
#include "window.h"

namespace bs {

	SDL_Event Window::event;


	Window::Window(const int& width, const int& height, const char* title, const int& x, const int& y, Uint32 flags)
		: m_width(width), m_height(height), m_title(title){

		flags |= SDL_WINDOW_OPENGL;

		this->m_window = SDL_CreateWindow(title, x, y, width, height, flags);
		SDL_PollEvent(&(Window::event));
		SDL_AddEventWatch(handleEvent, this);

		this->m_glContext = SDL_GL_CreateContext(this->m_window);
		SDL_GL_MakeCurrent(this->m_window, this->m_glContext);

		SDL_GL_SetSwapInterval(1);

	}

	Window::~Window() {

		SDL_GL_DeleteContext(this->m_glContext);

		SDL_DestroyWindow(this->m_window);

	}

	int Window::handleEvent(void* data, SDL_Event* event) {

		Window* w = (Window*)data;

		switch (event->type) {

		case SDL_WINDOWEVENT:

			if (event->window.windowID == SDL_GetWindowID(w->m_window)) {

				switch (event->window.event) {

					//RESIZED
				case SDL_WINDOWEVENT_RESIZED:
					SDL_GetWindowSize(w->m_window, &(w->m_width), &(w->m_height));
					glViewport(0, 0, w->m_width, w->m_height);
					w->onWindowResize();
					break;

					//MOVED
				case SDL_WINDOWEVENT_MOVED:
					SDL_GetWindowPosition(w->m_window, &(w->m_posX), &(w->m_posY));
					w->onWindowMove();
					break;

					//MAXIMIZED
				case SDL_WINDOWEVENT_MAXIMIZED:
					SDL_GetWindowPosition(w->m_window, &(w->m_posX), &(w->m_posY));
					SDL_GetWindowSize(w->m_window, &(w->m_width), &(w->m_height));
					glViewport(0, 0, w->m_width, w->m_height);
					w->onWindowMaximize();
					break;

					//MINIMIZED
				case SDL_WINDOWEVENT_MINIMIZED:
					SDL_GetWindowPosition(w->m_window, &(w->m_posX), &(w->m_posY));
					SDL_GetWindowSize(w->m_window, &(w->m_width), &(w->m_height));
					glViewport(0, 0, w->m_width, w->m_height);
					w->onWindowMinimize();
					break;

				case SDL_WINDOWEVENT_HIDDEN:
					SDL_GetWindowPosition(w->m_window, &(w->m_posX), &(w->m_posY));
					SDL_GetWindowSize(w->m_window, &(w->m_width), &(w->m_height));
					glViewport(0, 0, w->m_width, w->m_height);
					w->onWindowHide();
					break;

				case SDL_WINDOWEVENT_EXPOSED:
					w->onWindowExpose();
					break;

				case SDL_WINDOWEVENT_ENTER:
					w->onWindowEnter();
					break;

				case SDL_WINDOWEVENT_LEAVE:
					w->onWindowLeave();
					break;

				default:
					break;
				}

			}

			break;
		case SDL_MOUSEBUTTONDOWN:
			w->onMouseButtonDown(event->button);
			break;
		case SDL_MOUSEBUTTONUP:
			w->onMouseButtonUp(event->button);
			break;
		case SDL_MOUSEMOTION:
			w->onMouseMotion(event->motion);
			break;
		case SDL_MOUSEWHEEL:
			w->onMouseWheel(event->wheel);
			break;
		case SDL_KEYDOWN:
			w->onKeyDown(event->key.keysym.scancode);
			break;
		case SDL_KEYUP:
			w->onKeyUp(event->key.keysym.scancode);
			break;

		}

		return 0;

	}

	void Window::update() {

		SDL_PollEvent(&(Window::event));

		SDL_GL_SwapWindow(this->m_window);

	}

	bool Window::shouldClose() {

		if (Window::event.window.windowID == SDL_GetWindowID(this->m_window)) {
			return Window::event.window.event == SDL_WINDOWEVENT_CLOSE;
		}
		else {
			return false;
		}

	}


	//callback setter
	void Window::setWindowResizeCallback(callback_function resize) {

		this->resized = resize;

	}

	void Window::setWindowMoveCallback(callback_function move) {

		this->moved = move;

	}

	void Window::setWindowMaximizeCallback(callback_function maximize) {

		this->maximized = maximize;

	}

	void Window::setWindowMinimizeCallback(callback_function minimize) {

		this->minimized = minimize;

	}

	void Window::setWindowHideCallback(callback_function hide) {

		this->hidden = hide;

	}

	void Window::setWindowExposeCallback(callback_function expose) {

		this->exposed = expose;

	}

	void Window::setWindowEnterCallback(callback_function enter) {

		this->entered = enter;

	}

	void Window::setWindowLeaveCallback(callback_function leave) {

		this->left = leave;

	}

	void Window::setMouseButtonDownCallback(callback_function mousebuttondown) {

		this->mousebuttondown = mousebuttondown;

	}

	void Window::setMouseButtonUpCallback(callback_function mousebuttonup) {

		this->mousebuttonup = mousebuttonup;

	}

	void Window::setMouseMotionCallback(callback_function mousemotion) {

		this->mousemotion = mousemotion;

	}

	void Window::setMouseWheelCallback(callback_function mousewheel) {

		this->mousewheel = mousewheel;

	}

	void Window::setKeyDownCallback(callback_function keydown) {

		this->keydown = keydown;

	}

	void Window::setKeyUpCallback(callback_function keyup) {

		this->keyup = keyup;

	}


	//callback execution
	void Window::onWindowResize() {

		if (this->resized) this->resized();
	}

	void Window::onWindowMove() {

		if (this->moved) this->moved();
	}

	void Window::onWindowMaximize() {

		if (this->maximized) this->maximized();

	}

	void Window::onWindowMinimize() {

		if (this->minimized) this->minimized();

	}

	void Window::onWindowHide() {

		if (this->hidden) this->hidden();

	}

	void Window::onWindowExpose() {

		if (this->exposed) this->exposed();

	}

	void Window::onWindowEnter() {

		if (this->entered) this->entered();

	}

	void Window::onWindowLeave() {

		if (this->left) this->left();

	}

	void Window::onMouseButtonDown(SDL_MouseButtonEvent mousecode) {
	
		int key = getMouseCode(mousecode);

		this->m_mousebuttonstate |= (1ULL << key);

		if (this->mousebuttondown) this->mousebuttondown();
	
	}
	void Window::onMouseButtonUp(SDL_MouseButtonEvent mousecode) {
	
		int key = getMouseCode(mousecode);

		this->m_mousebuttonstate &= ~(1ULL << key);

		if (this->mousebuttonup) this->mousebuttonup();
	
	}
	
	void Window::onMouseMotion(SDL_MouseMotionEvent mousecode) {

		this->mousePosX = mousecode.x;
		this->mousePosY = mousecode.y;
	
		if (this->mousemotion) this->mousemotion();
	
	}

	void Window::onMouseWheel(SDL_MouseWheelEvent mousecode) {
	
		this->mouseWheelDirection = mousecode.direction;

		if (this->mousewheel) this->mousewheel();
	
	}

	void Window::onKeyDown(SDL_Scancode scancode) {

		int key = getKeyCode(scancode);

		this->m_keystate |= (1ULL << key);

		if (this->keydown) this->keydown();

	}

	void Window::onKeyUp(SDL_Scancode scancode) {

		int key = getKeyCode(scancode);

		this->m_keystate &= ~(1ULL << key);

		if (this->keyup) this->keyup();

	}

	KeyCode Window::getKeyCode(SDL_Scancode scancode) {

		int key;

		switch (scancode) {
		case SDL_SCANCODE_0:
			key = BSK_0;
			break;
		case SDL_SCANCODE_1:
			key = BSK_1;
			break;
		case SDL_SCANCODE_2:
			key = BSK_2;
			break;
		case SDL_SCANCODE_3:
			key = BSK_3;
			break;
		case SDL_SCANCODE_4:
			key = BSK_4;
			break;
		case SDL_SCANCODE_5:
			key = BSK_5;
			break;
		case SDL_SCANCODE_6:
			key = BSK_6;
			break;
		case SDL_SCANCODE_7:
			key = BSK_7;
			break;
		case SDL_SCANCODE_8:
			key = BSK_8;
			break;
		case SDL_SCANCODE_9:
			key = BSK_9;
			break;
		case SDL_SCANCODE_A:
			key = BSK_A;
			break;
		case SDL_SCANCODE_B:
			key = BSK_B;
			break;
		case SDL_SCANCODE_C:
			key = BSK_C;
			break;
		case SDL_SCANCODE_D:
			key = BSK_D;
			break;
		case SDL_SCANCODE_E:
			key = BSK_E;
			break;
		case SDL_SCANCODE_F:
			key = BSK_F;
			break;
		case SDL_SCANCODE_G:
			key = BSK_G;
			break;
		case SDL_SCANCODE_H:
			key = BSK_H;
			break;
		case SDL_SCANCODE_I:
			key = BSK_I;
			break;
		case SDL_SCANCODE_J:
			key = BSK_J;
			break;
		case SDL_SCANCODE_K:
			key = BSK_K;
			break;
		case SDL_SCANCODE_L:
			key = BSK_L;
			break;
		case SDL_SCANCODE_M:
			key = BSK_M;
			break;
		case SDL_SCANCODE_N:
			key = BSK_N;
			break;
		case SDL_SCANCODE_O:
			key = BSK_O;
			break;
		case SDL_SCANCODE_P:
			key = BSK_P;
			break;
		case SDL_SCANCODE_Q:
			key = BSK_Q;
			break;
		case SDL_SCANCODE_R:
			key = BSK_R;
			break;
		case SDL_SCANCODE_S:
			key = BSK_S;
			break;
		case SDL_SCANCODE_T:
			key = BSK_T;
			break;
		case SDL_SCANCODE_U:
			key = BSK_U;
			break;
		case SDL_SCANCODE_V:
			key = BSK_V;
			break;
		case SDL_SCANCODE_W:
			key = BSK_W;
			break;
		case SDL_SCANCODE_X:
			key = BSK_X;
			break;
		case SDL_SCANCODE_Y:
			key = BSK_Y;
			break;
		case SDL_SCANCODE_Z:
			key = BSK_Z;
			break;
		case SDL_SCANCODE_ESCAPE:
			key = BSK_ESCAPE;
			break;
		case SDL_SCANCODE_UP:
			key = BSK_UP;
			break;
		case SDL_SCANCODE_DOWN:
			key = BSK_DOWN;
			break;
		case SDL_SCANCODE_LEFT:
			key = BSK_LEFT;
			break;
		case SDL_SCANCODE_RIGHT:
			key = BSK_RIGHT;
			break;
		case SDL_SCANCODE_RSHIFT:
			key = BSK_RSHIFT;
			break;
		case SDL_SCANCODE_LSHIFT:
			key = BSK_LSHIFT;
			break;
		case SDL_SCANCODE_SPACE:
			key = BSK_SPACE;
			break;
		case SDL_SCANCODE_KP_0:
			key = BSK_NP0;
			break;
		case SDL_SCANCODE_KP_1:
			key = BSK_NP1;
			break;
		case SDL_SCANCODE_KP_2:
			key = BSK_NP2;
			break;
		case SDL_SCANCODE_KP_3:
			key = BSK_NP3;
			break;
		case SDL_SCANCODE_KP_4:
			key = BSK_NP4;
			break;
		case SDL_SCANCODE_KP_5:
			key = BSK_NP5;
			break;
		case SDL_SCANCODE_KP_6:
			key = BSK_NP6;
			break;
		case SDL_SCANCODE_KP_7:
			key = BSK_NP7;
			break;
		case SDL_SCANCODE_KP_8:
			key = BSK_NP8;
			break;
		case SDL_SCANCODE_KP_9:
			key = BSK_NP9;
			break;
		case SDL_SCANCODE_RETURN:
			key = BSK_ENTER;
			break;
		case SDL_SCANCODE_COMMA:
			key = BSK_COMMA;
			break;
		case SDL_SCANCODE_PERIOD:
			key = BSK_PERIOD;
			break;
		default:
			key = -1;
			break;
		}

		return (KeyCode)key;

	}

	MouseCode Window::getMouseCode(SDL_MouseButtonEvent mousecode) {

		int key;

		switch (mousecode.button) {
		case SDL_BUTTON_LEFT:
			key = MOUSE_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			key = MOUSE_MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			key = MOUSE_RIGHT;
			break;
		case SDL_BUTTON_X1:
			key = MOUSE_X1;
			break;
		case SDL_BUTTON_X2:
			key = MOUSE_X2;
			break;
		default:
			key = -1;
			break;
		}

		return (MouseCode)key;

	}




	SDL_Window* Window::getWindow() {
		return this->m_window;
	}

	SDL_GLContext& Window::getContext() {
		return this->m_glContext;
	}

}
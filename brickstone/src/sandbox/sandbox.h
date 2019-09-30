#pragma once
#include <iostream>
#include <application/application.h>
#include <logging/log.h>
#include <window/window.h>


class Sandbox : public bs::Application {

private:
	bs::Window* w = nullptr;

public:
	Sandbox() {}
	~Sandbox() {}

	void init();
	void run();

};

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <render/renderer.h>
#include <application/application.h>
#include <logging/log.h>
#include <window/window.h>
#include <scene/camera.h>
#include <model/material.h>
#include <model/texture.h>
#include <model/model.h>
#include <terrain/terrain.h>
#include <math/maths.h>

class Sandbox : public bs::Application {

private:
	bs::Window* w = nullptr;

public:
	Sandbox() {}
	~Sandbox() {}

	void init();
	void run();

};

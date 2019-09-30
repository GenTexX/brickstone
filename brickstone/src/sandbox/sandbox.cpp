#include <bspch.h>
#include "sandbox.h"

void Sandbox::init() {

	this->w = new bs::Window(1024, 768);

}

void Sandbox::run() {


	while (!this->w->shouldClose()) {



		this->w->update();
	}

}

#include <bspch.h>
#include "Camera.h"

namespace bs {


	camera::camera() {
	}

	camera::~camera() {
	}

	mat4 camera::getViewMatrix() {
		return mat4::translation(vec3(-(this->x), -(this->y), -(this->z)));
	}
}

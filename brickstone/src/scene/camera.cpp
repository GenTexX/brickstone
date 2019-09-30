#include "Camera.h"

namespace bs {


	Camera::Camera() {
	}

	Camera::~Camera() {
	}

	mat4 Camera::getViewMatrix() {
		return mat4::translation(vec3(-(this->x), -(this->y), -(this->z)));
	}
}

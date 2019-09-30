#pragma once
#include "../math/maths.h"

namespace bs {


	struct Camera {

		float x, y, z;

		Camera();
		~Camera();

		mat4 getViewMatrix();

	};

}
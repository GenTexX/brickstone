#pragma once
#include "../math/maths.h"

namespace bs {


	struct camera {

		float x, y, z;

		camera();
		~camera();

		mat4 getViewMatrix();

	};

}
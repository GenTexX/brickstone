#pragma once
#include <math/maths.h>

namespace bs {
		
	enum LightType {

		DirectionalLight = 0,
		PointLight = 1,
		SpotLight = 2

	};

	struct light {

		vec3 m_Position;
		vec3 m_Direction;

		vec3 m_Ambient;
		vec3 m_Diffuse;
		vec3 m_Specular;

	};

	struct directionalLight : public light {


	};

	struct pointLight : public light {

		float m_Constant;
		float m_Linear;
		float m_Quadratic;

	};

	struct spotLight : public pointLight {

		float innerCutOff;
		float outerCutOff;

	};


}
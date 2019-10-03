#pragma once
#include <math/maths.h>

namespace bs {

	class Material {

	private:
		bs::vec3 m_Ambient;
		bs::vec3 m_Diffuse;
		bs::vec3 m_Specular;
		float m_Shininess;

	public:
		Material(bs::vec3 ambient = bs::vec3(1.0f, 1.0f, 1.0f), bs::vec3 diffuse = bs::vec3(1.0f, 1.0f, 1.0f), bs::vec3 specular = bs::vec3(1.0f, 1.0f, 1.0f), float shininess = 32);
		~Material();

		bs::vec3& getAmbient();
		bs::vec3& getDiffuse();
		bs::vec3& getSpecular();
		float& getShininess();
	
	};

}
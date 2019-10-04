#pragma once
#include <math/maths.h>
#include <texture/texture.h>
#include <string>

namespace bs {

	class Material {

	private:
		vec3 m_Ambient;
		vec3 m_Diffuse;
		Texture m_DiffuseMap;
		bool m_UseDiffuseMap;
		vec3 m_Specular;
		float m_Shininess;

	public:
		Material(vec3 ambient = vec3(1.0f, 1.0f, 1.0f), vec3 diffuse = vec3(1.0f, 1.0f, 1.0f), vec3 specular = vec3(1.0f, 1.0f, 1.0f), float shininess = 32);
		~Material();

		vec3& getAmbient();
		vec3& getDiffuse();
		Texture& getDiffuseMap();
		bool isUsingDiffuseMap();
		vec3& getSpecular();
		float& getShininess();

		void loadDiffuseMap(const std::string& path);

	
	};

}
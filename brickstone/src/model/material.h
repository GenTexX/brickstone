#pragma once
#include <math/maths.h>
#include <model/texture.h>
#include <string>

namespace bs {

	class Material {

	private:
		vec3 m_Ambient;
		vec3 m_Diffuse;
		Texture m_DiffuseMap;
		bool m_UseDiffuseMap;
		Texture m_SpecularMap;
		bool m_UseSpecularMap;
		vec3 m_Specular;
		float m_Shininess;

	public:
		Material(vec3 ambient = vec3(1.0f, 1.0f, 1.0f), vec3 diffuse = vec3(1.0f, 1.0f, 1.0f), vec3 specular = vec3(1.0f, 1.0f, 1.0f), float shininess = 32);
		~Material();

		vec3& getAmbient();
		vec3& getDiffuse();
		vec3& getSpecular();
		float& getShininess();

		//diffuseMap
		Texture& getDiffuseMap();
		bool isUsingDiffuseMap();
		void loadDiffuseMap(const std::string& path);

		//specularMap
		Texture& getSpecularMap();
		bool isUsingSpecularMap();
		void loadSpecularMap(const std::string& path);

	
	};

}
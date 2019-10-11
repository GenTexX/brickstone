#include <bspch.h>
#include "material.h"

namespace bs {

	Material::Material(bs::vec3 ambient, bs::vec3 diffuse, bs::vec3 specular, float shininess) 
		: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess), m_UseDiffuseMap(false), m_UseSpecularMap(false) {

	}

	Material::~Material() {

	}

	bs::vec3& Material::getAmbient() {
		return this->m_Ambient;
	}

	bs::vec3& Material::getDiffuse() {
		return this->m_Diffuse;
	}

	Texture& Material::getDiffuseMap() {
		return this->m_DiffuseMap;
	}

	bool Material::isUsingSpecularMap()
	{
		return this->m_UseSpecularMap;
	}

	Texture& Material::getSpecularMap() {
		return this->m_SpecularMap;
	}

	bool Material::isUsingDiffuseMap()
	{
		return this->m_UseDiffuseMap;
	}

	bs::vec3& Material::getSpecular() {
		return this->m_Specular;
	}

	float& Material::getShininess() {
		return this->m_Shininess;
	}

	void Material::loadDiffuseMap(const std::string& path) {
		this->m_DiffuseMap.loadTexture(path, 0);
		m_UseDiffuseMap = true;
	}

	void Material::loadSpecularMap(const std::string& path) {
		this->m_SpecularMap.loadTexture(path, 1);
		m_UseSpecularMap = true;
	}


}
#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math/maths.h>
#include <model/material.h>
#include <logging/log.h>
#include <scene/light.h>

namespace bs {

	class Shader {
	private:

		unsigned int m_VertexId;
		unsigned int m_TessControlId;
		unsigned int m_TessEvaluationId;
		unsigned int m_GeometryId;
		unsigned int m_FragmentId;
		unsigned int m_Program;


		std::string m_VertexSrc;
		std::string m_ControlSrc;
		std::string m_EvaluationSrc;
		std::string m_GeometrySrc;
		std::string m_FragmentSrc;

		unsigned int m_DirectionalLightCount = 0;
		unsigned int m_PointLightCount = 0;
		unsigned int m_SpotLightCount = 0;

		int compile();

	public:

		Shader();
		~Shader();

		void setUniform1i(const char* name, const int& val);
		void setUniform1iv(const char* name, const std::vector<int>& val);
		void setUniform1f(const char* name, const float& val);
		void setUniform2f(const char* name, const bs::vec2& val);
		void setUniform3f(const char* name, bs::vec3 val);
		void setUniformMat4(const char* name, const bs::mat4& val);
		void setUniformMaterial(Material& val);

		int readSource(const std::string& filePath);
		int create();
		void bind();

		std::string& getVertexSource();
		std::string& getTessControlSource();
		std::string& getTessEvaluationSource();
		std::string& getGeometrySource();
		std::string& getFragmentSource();

		void addDirectionalLight(directionalLight light, int index = -1);
		void addPointLight(pointLight light, int index = -1);
		void addSpotLight(spotLight light, int index = -1);

	};

}
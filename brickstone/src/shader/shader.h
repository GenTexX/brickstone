#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../file/FileHandler.h"
#include "../math/maths.h"

namespace bs {

	class Shader {
	private:

		unsigned int vertexId;
		unsigned int tessControlId;
		unsigned int tessEvaluationId;
		unsigned int geometryId;
		unsigned int fragmentId;
		unsigned int program;


		std::string vertexSrc;
		std::string controlSrc;
		std::string evaluationSrc;
		std::string geometrySrc;
		std::string fragmentSrc;

	public:

		Shader();
		~Shader();

		void setUniform1i(const char* name, const int& val);
		void setUniform3f(const char* name, bs::vec3 val);
		void setUniformMat4(const char* name, const bs::mat4& val);

		int readSource(const std::string& filePath);
		int compile();
		int create();
		void bind();

		std::string& getVertexSource();
		std::string& getTessControlSource();
		std::string& getTessEvaluationSource();
		std::string& getGeometrySource();
		std::string& getFragmentSource();

	};

}
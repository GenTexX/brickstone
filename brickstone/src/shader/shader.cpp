#include <bspch.h>
#include "Shader.h"

namespace bs {

	Shader::Shader() {

		this->m_Program = 0;

		this->m_VertexId = 0;
		this->m_TessControlId = 0;
		this->m_TessEvaluationId = 0;
		this->m_GeometryId = 0;
		this->m_FragmentId = 0;

	}

	Shader::~Shader() {


	}


	int Shader::readSource(const std::string& path) {

		/* open shader file */
		FILE* shaderFile;
		shaderFile = fopen(path.c_str(), "r");

		std::stringstream vertex;
		std::stringstream tessControl;
		std::stringstream tessEvaluation;
		std::stringstream geometry;
		std::stringstream fragment;

		/* process shader file */
		char cstr_line[150];
		enum ShaderMode { NONE = -1, VERTEX = 0, CONTROL = 1, EVALUATION = 2, GEOMETRY = 3, FRAGMENT = 4 };
		ShaderMode mode = NONE;
		while (!feof(shaderFile)) {
			fgets(cstr_line, 150, shaderFile);
			std::string line = cstr_line;
			/* select shader type */
			if (line.find("#shader") != std::string::npos) {

				if (line.find("vertex") != std::string::npos)
					mode = VERTEX;

				if (line.find("control") != std::string::npos)
					mode = CONTROL;

				if (line.find("evaluation") != std::string::npos)
					mode = EVALUATION;

				if (line.find("geometry") != std::string::npos)
					mode = GEOMETRY;

				if (line.find("fragment") != std::string::npos)
					mode = FRAGMENT;

				continue;

			}

			/* read shader source */
			switch (mode) {

			case NONE:
				break;

			case VERTEX:
				vertex << line << std::endl;
				break;

			case CONTROL:
				tessControl << line << std::endl;
				break;

			case EVALUATION:
				tessEvaluation << line << std::endl;
				break;

			case GEOMETRY:
				geometry << line << std::endl;
				break;

			case FRAGMENT:
				fragment << line << std::endl;
				break;

			default:
				break;
			}

		}

		fclose(shaderFile);

		this->m_VertexSrc = vertex.str();
		this->m_ControlSrc = tessControl.str();
		this->m_EvaluationSrc = tessEvaluation.str();
		this->m_GeometrySrc = geometry.str();
		this->m_FragmentSrc = fragment.str();

		return 0;

	}

	void Shader::setUniform1i(const char * name, const int & val) {
	
		glUniform1i(glGetUniformLocation(this->m_Program, name), val);
	
	}

	void Shader::setUniform1iv(const char* name, const std::vector<int>& val) {

		glUniform1iv(glGetUniformLocation(this->m_Program, name), (GLsizei) val.size(), val.data());

	}

	void Shader::setUniform1f(const char* name, const float& val) {
	
		glUniform1f(glGetUniformLocation(this->m_Program, name), val);
	
	}

	void Shader::setUniform2f(const char* name, const bs::vec2& val) {
	
		glUniform2f(glGetUniformLocation(this->m_Program, name), val.x, val.y);
	
	}

	void Shader::setUniform3f(const char * name, bs::vec3 val) {
		
		glUniform3f(glGetUniformLocation(this->m_Program, name), val.x, val.y, val.z);
	
	}

	void Shader::setUniformMat4(const char * name, const bs::mat4 & val) {
	

		int location = glGetUniformLocation(this->m_Program, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, val.elements);
	
	}

	void Shader::setUniformMaterial(Material& val) {
	
		this->setUniform3f("u_Material.ambient", val.getAmbient());
		this->setUniform3f("u_Material.diffuse", val.getDiffuse());
		this->setUniform3f("u_Material.specular", val.getSpecular());
		this->setUniform1f("u_Material.shininess", val.getShininess());
		this->setUniform1i("u_Material.useDiffuseMap", val.isUsingDiffuseMap());
		this->setUniform1i("u_Material.diffuseMap", val.getDiffuseMap().getSlot());
		this->setUniform1i("u_Material.useSpecularMap", val.isUsingSpecularMap());
		this->setUniform1i("u_Material.specularMap", val.getSpecularMap().getSlot());
		if(val.isUsingDiffuseMap())
			val.getDiffuseMap().bind();
		if(val.isUsingSpecularMap())
			val.getSpecularMap().bind();
	}

	int Shader::create() {

		/* delete old program */
		if (this->m_Program) glDeleteProgram(this->m_Program);

		/* compile shaders */
		if (this->compile() < 0) return -1;

		this->m_Program = glCreateProgram();

		if (!this->m_Program) {

			BS_CORE_ERROR("Failed to create Shader!");
			return -1;

		}

		/* attach shaders */
		glAttachShader(this->m_Program, this->m_VertexId);
		glAttachShader(this->m_Program, this->m_FragmentId);

		/* link shader program */
		glLinkProgram(this->m_Program);

		/* validate shader program */
		glValidateProgram(this->m_Program);

		/* check for shader validation errors*/
		int programValidation;
		glGetProgramiv(this->m_Program, GL_VALIDATE_STATUS, &programValidation);
		if (!programValidation) {

			std::cout << "Shaderprogram validationfailed." << std::endl;

		}

		/* delete shaders */
		glDeleteShader(this->m_VertexId);
		glDeleteShader(this->m_FragmentId);

		return 0;
	}

	int Shader::compile() {

		/* create empty shader objects*/
		if (!this->m_VertexSrc.empty()) this->m_VertexId = glCreateShader(GL_VERTEX_SHADER);
		if (!this->m_ControlSrc.empty()) this->m_TessControlId = glCreateShader(GL_TESS_CONTROL_SHADER);
		if (!this->m_EvaluationSrc.empty()) this->m_TessEvaluationId = glCreateShader(GL_TESS_EVALUATION_SHADER);
		if (!this->m_GeometrySrc.empty()) this->m_GeometryId = glCreateShader(GL_GEOMETRY_SHADER);
		if (!this->m_FragmentSrc.empty()) this->m_FragmentId = glCreateShader(GL_FRAGMENT_SHADER);


		/* compile shader */

		/************************************/
		/********** VERTEX SHADER ***********/
		/************************************/
		if (this->m_VertexId) {

			/* set vertex shader source */
			const char* vertexShaderSource = this->m_VertexSrc.c_str();
			glShaderSource(this->m_VertexId, 1, &vertexShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->m_VertexId);

			/* check for compilation errors */
			int vertexCompilationResult;
			glGetShaderiv(this->m_VertexId, GL_COMPILE_STATUS, &vertexCompilationResult);
			if (vertexCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_VertexId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*) _malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_VertexId, length, &length, msg);

				std::cout << "Failed to compile Vertex Shader" << std::endl;
				std::cout << msg << std::endl;

				return -2;

			}

		}

		/************************************/
		/******* TESS CONTROL SHADER ********/
		/************************************/
		if (this->m_TessControlId) {

			/* set control shader source */
			const char* controlShaderSource = this->m_ControlSrc.c_str();
			glShaderSource(this->m_TessControlId, 1, &controlShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->m_TessControlId);

			/* check for compilation errors*/
			int controlCompilationResult;
			glGetShaderiv(this->m_TessControlId, GL_COMPILE_STATUS, &controlCompilationResult);
			if (controlCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_TessControlId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*) _malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_TessControlId, length, &length, msg);

				std::cout << "Failed to compile tess control Shader" << std::endl;
				std::cout << msg << std::endl;

				return -2;

			}

		}

		/************************************/
		/****** TESS EVALUATION SHADER ******/
		/************************************/
		if (this->m_TessEvaluationId) {

			/* set control shader source */
			const char* evaluationShaderSource = this->m_EvaluationSrc.c_str();
			glShaderSource(this->m_TessEvaluationId, 1, &evaluationShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->m_TessEvaluationId);

			/* check for compilation errors*/
			int evaluationCompilationResult;
			glGetShaderiv(this->m_TessEvaluationId, GL_COMPILE_STATUS, &evaluationCompilationResult);
			if (evaluationCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_TessEvaluationId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*) _malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_TessEvaluationId, length, &length, msg);

				std::cout << "Failed to compile tess evaluation Shader" << std::endl;
				std::cout << msg << std::endl;

				return -3;

			}

		}

		/************************************/
		/********* GEOMETRY SHADER **********/
		/************************************/
		if (this->m_GeometryId) {

			/* set control shader source */
			const char* geometryShaderSource = this->m_GeometrySrc.c_str();
			glShaderSource(this->m_GeometryId, 1, &geometryShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->m_GeometryId);

			/* check for compilation errors*/
			int geometryCompilationResult;
			glGetShaderiv(this->m_GeometryId, GL_COMPILE_STATUS, &geometryCompilationResult);
			if (geometryCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_GeometryId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*) _malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_GeometryId, length, &length, msg);

				std::cout << "Failed to compile tess geometry Shader" << std::endl;
				std::cout << msg << std::endl;

				return -4;

			}

		}

		/************************************/
		/********* FRAGMENT SHADER **********/
		/************************************/
		if (this->m_FragmentId) {

			/* set fragment shader source */
			const char* fragmentShaderSource = this->m_FragmentSrc.c_str();
			glShaderSource(this->m_FragmentId, 1, &fragmentShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->m_FragmentId);

			/* check for compilation errors*/
			int fragmentCompilationResult;
			glGetShaderiv(this->m_FragmentId, GL_COMPILE_STATUS, &fragmentCompilationResult);
			if (fragmentCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_FragmentId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*) _malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_FragmentId, length, &length, msg);

				std::cout << "Failed to compile Fragment Shader" << std::endl;
				std::cout << msg << std::endl;

				return -5;

			}

		}

		return 0;
	}

	void Shader::bind() {

		glUseProgram(this->m_Program);

	}


	std::string& Shader::getVertexSource() {

		return this->m_VertexSrc;

	}
	
	std::string& Shader::getTessControlSource() {

		return this->m_ControlSrc;

	}

	std::string& Shader::getTessEvaluationSource() {

		return this->m_EvaluationSrc;

	}

	std::string& Shader::getGeometrySource() {

		return this->m_GeometrySrc;

	}

	std::string& Shader::getFragmentSource() {

		return this->m_FragmentSrc;

	}

}
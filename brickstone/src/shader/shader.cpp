#include <bspch.h>
#include "Shader.h"

namespace bs {

	Shader::Shader() {

		this->program = 0;

		this->vertexId = 0;
		this->tessControlId = 0;
		this->tessEvaluationId = 0;
		this->geometryId = 0;
		this->fragmentId = 0;

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

		this->vertexSrc = vertex.str();
		this->controlSrc = tessControl.str();
		this->evaluationSrc = tessEvaluation.str();
		this->geometrySrc = geometry.str();
		this->fragmentSrc = fragment.str();

		return 0;

	}

	void Shader::setUniform1i(const char * name, const int & val) {
	
		glUniform1i(glGetUniformLocation(this->program, name), val);
	
	}

	void Shader::setUniform1f(const char* name, const float& val) {
	
		glUniform1f(glGetUniformLocation(this->program, name), val);
	
	}

	void Shader::setUniform2f(const char* name, const bs::vec2& val) {
	
		glUniform2f(glGetUniformLocation(this->program, name), val.x, val.y);
	
	}

	void Shader::setUniform3f(const char * name, bs::vec3 val) {
		
		glUniform3f(glGetUniformLocation(this->program, name), val.x, val.y, val.z);
	
	}

	void Shader::setUniformMat4(const char * name, const bs::mat4 & val) {
	

		int location = glGetUniformLocation(this->program, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, val.elements);
	
	}

	void Shader::setUniformMaterial(const char* name, Material val) {
	
		this->setUniform3f("u_Material.ambient", val.getAmbient());
		this->setUniform3f("u_Material.diffuse", val.getDiffuse());
		this->setUniform3f("u_Material.specular", val.getSpecular());
	
	}

	int Shader::create() {

		/* delete old program */
		if (this->program) glDeleteProgram(this->program);

		/* compile shaders */
		if (this->compile() < 0) return -1;

		this->program = glCreateProgram();

		if (!this->program) {

			std::cout << "Failed to create shader program" << std::endl;
			return -1;

		}

		/* attach shaders */
		glAttachShader(this->program, this->vertexId);
		glAttachShader(this->program, this->fragmentId);

		/* link shader program */
		glLinkProgram(this->program);

		/* validate shader program */
		glValidateProgram(this->program);

		/* check for shader validation errors*/
		int programValidation;
		glGetProgramiv(this->program, GL_VALIDATE_STATUS, &programValidation);
		if (!programValidation) {

			std::cout << "Shaderprogram validationfailed." << std::endl;

		}

		/* delete shaders */
		glDeleteShader(this->vertexId);
		glDeleteShader(this->fragmentId);

		return 0;
	}

	int Shader::compile() {

		/* create empty shader objects*/
		if (!this->vertexSrc.empty()) this->vertexId = glCreateShader(GL_VERTEX_SHADER);
		if (!this->controlSrc.empty()) this->tessControlId = glCreateShader(GL_TESS_CONTROL_SHADER);
		if (!this->evaluationSrc.empty()) this->tessEvaluationId = glCreateShader(GL_TESS_EVALUATION_SHADER);
		if (!this->geometrySrc.empty()) this->geometryId = glCreateShader(GL_GEOMETRY_SHADER);
		if (!this->fragmentSrc.empty()) this->fragmentId = glCreateShader(GL_FRAGMENT_SHADER);


		

		/* compile shader */

		/************************************/
		/********** VERTEX SHADER ***********/
		/************************************/
		if (this->vertexId) {

			/* set vertex shader source */
			const char* vertexShaderSource = this->vertexSrc.c_str();
			glShaderSource(this->vertexId, 1, &vertexShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->vertexId);

			/* check for compilation errors */
			int vertexCompilationResult;
			glGetShaderiv(this->vertexId, GL_COMPILE_STATUS, &vertexCompilationResult);
			if (vertexCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->vertexId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(this->vertexId, length, &length, msg);

				std::cout << "Failed to compile Vertex Shader" << std::endl;
				std::cout << msg << std::endl;

				return -2;

			}

		}

		/************************************/
		/******* TESS CONTROL SHADER ********/
		/************************************/
		if (this->tessControlId) {

			/* set control shader source */
			const char* controlShaderSource = this->controlSrc.c_str();
			glShaderSource(this->tessControlId, 1, &controlShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->tessControlId);

			/* check for compilation errors*/
			int controlCompilationResult;
			glGetShaderiv(this->tessControlId, GL_COMPILE_STATUS, &controlCompilationResult);
			if (controlCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->tessControlId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(this->tessControlId, length, &length, msg);

				std::cout << "Failed to compile tess control Shader" << std::endl;
				std::cout << msg << std::endl;

				return -2;

			}

		}

		/************************************/
		/****** TESS EVALUATION SHADER ******/
		/************************************/
		if (this->tessEvaluationId) {

			/* set control shader source */
			const char* evaluationShaderSource = this->evaluationSrc.c_str();
			glShaderSource(this->tessEvaluationId, 1, &evaluationShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->tessEvaluationId);

			/* check for compilation errors*/
			int evaluationCompilationResult;
			glGetShaderiv(this->tessEvaluationId, GL_COMPILE_STATUS, &evaluationCompilationResult);
			if (evaluationCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->tessEvaluationId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(this->tessEvaluationId, length, &length, msg);

				std::cout << "Failed to compile tess evaluation Shader" << std::endl;
				std::cout << msg << std::endl;

				return -3;

			}

		}

		/************************************/
		/********* GEOMETRY SHADER **********/
		/************************************/
		if (this->geometryId) {

			/* set control shader source */
			const char* geometryShaderSource = this->geometrySrc.c_str();
			glShaderSource(this->geometryId, 1, &geometryShaderSource, nullptr);

			/* compile control shader */
			glCompileShader(this->geometryId);

			/* check for compilation errors*/
			int geometryCompilationResult;
			glGetShaderiv(this->geometryId, GL_COMPILE_STATUS, &geometryCompilationResult);
			if (geometryCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->geometryId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(this->geometryId, length, &length, msg);

				std::cout << "Failed to compile tess geometry Shader" << std::endl;
				std::cout << msg << std::endl;

				return -4;

			}

		}

		/************************************/
		/********* FRAGMENT SHADER **********/
		/************************************/
		if (this->fragmentId) {

			/* set fragment shader source */
			const char* fragmentShaderSource = this->fragmentSrc.c_str();
			glShaderSource(this->fragmentId, 1, &fragmentShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->fragmentId);

			/* check for compilation errors*/
			int fragmentCompilationResult;
			glGetShaderiv(this->fragmentId, GL_COMPILE_STATUS, &fragmentCompilationResult);
			if (fragmentCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->fragmentId, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(this->fragmentId, length, &length, msg);

				std::cout << "Failed to compile Fragment Shader" << std::endl;
				std::cout << msg << std::endl;

				return -5;

			}

		}

		return 0;
	}

	void Shader::bind() {

		glUseProgram(this->program);

	}


	std::string& Shader::getVertexSource() {

		return this->vertexSrc;

	}
	
	std::string& Shader::getTessControlSource() {

		return this->controlSrc;

	}

	std::string& Shader::getTessEvaluationSource() {

		return this->evaluationSrc;

	}

	std::string& Shader::getGeometrySource() {

		return this->geometrySrc;

	}

	std::string& Shader::getFragmentSource() {

		return this->fragmentSrc;

	}

}
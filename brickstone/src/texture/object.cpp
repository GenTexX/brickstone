#include "Object.h"

bs::Object::Object() {



}

bs::Object::~Object() {


}

void bs::Object::readFile(const std::string & path) {

	FILE* objFile;
	objFile = fopen(path.c_str(), "r");

	std::vector<float> vertexBuffer;

	std::vector<vec3> positions;
	std::vector<vec2> textures;
	std::vector<vec3> normals;
	std::vector<unsigned int> indPositions;
	std::vector<unsigned int> indTextures;
	std::vector<unsigned int> indNormals;

	/* read data */
	char line[150];
	while (!feof(objFile)) {
		fgets(line, 150, objFile);
		if (line[0] == 'v') {
			if (line[1] == ' ') {

				//get vertecies
				std::vector<std::string> l = bs::split(line, ' ');

				float x, y, z;
				x = (float)std::atof(l[1].c_str());
				y = (float)std::atof(l[2].c_str());
				z = (float)std::atof(l[3].c_str());

				positions.push_back(vec3(x, y, z));

			}
			else if (line[1] == 't') {
				//get normals
				std::vector<std::string> l = bs::split(line, ' ');

				float x, y;
				x = (float)std::atof(l[1].c_str());
				y = (float)std::atof(l[2].c_str());

				textures.push_back(vec2(x, y));

			}
			else if (line[1] == 'n') {
				//get normals
				std::vector<std::string> l = bs::split(line, ' ');

				float x, y, z;
				x = (float)std::atof(l[1].c_str());
				y = (float)std::atof(l[2].c_str());
				z = (float)std::atof(l[3].c_str());

				normals.push_back(vec3(x, y, z));

			}
		}
		else if (line[0] == 'f') {

			//get faces
			std::vector<std::string> l = bs::split(line, ' ');
			std::vector<int> tmpPositions;
			std::vector<int> tmpTextures;
			std::vector<int> tmpNormals;

			for (size_t i = 1; i < l.size(); i++) {

				std::vector<std::string> d = (bs::split(l[i], '/'));

				int position = atoi(d[0].c_str());
				int texture = 0;
				int normal = 0;

				if (d.size() > 1) {
					texture = atoi(d[1].c_str());
					if (d.size() > 2) {
						normal = atoi(d[2].c_str());

					}
				}
				if (l.size() == 4) {
					indPositions.push_back(position - 1);
					if (texture + 1)
						indTextures.push_back(texture - 1);
					if (normal + 1)
						indNormals.push_back(normal - 1);
				}
				else {
					tmpPositions.push_back((position - 1));
					tmpTextures.push_back((texture - 1));
					tmpNormals.push_back((normal - 1));
				}


			}
			if (l.size() > 4) {
				indPositions.push_back(tmpPositions[0]);
				indPositions.push_back(tmpPositions[1]);
				indPositions.push_back(tmpPositions[2]);
				indPositions.push_back(tmpPositions[0]);
				indPositions.push_back(tmpPositions[2]);
				indPositions.push_back(tmpPositions[3]);

				if (tmpTextures.size() > 3) {
					indTextures.push_back(tmpTextures[0]);
					indTextures.push_back(tmpTextures[1]);
					indTextures.push_back(tmpTextures[2]);
					indTextures.push_back(tmpTextures[0]);
					indTextures.push_back(tmpTextures[2]);
					indTextures.push_back(tmpTextures[3]);
				}

				if (tmpNormals.size() > 3) {
					indNormals.push_back(tmpNormals[0]);
					indNormals.push_back(tmpNormals[1]);
					indNormals.push_back(tmpNormals[2]);
					indNormals.push_back(tmpNormals[0]);
					indNormals.push_back(tmpNormals[2]);
					indNormals.push_back(tmpNormals[3]);
				}
			}

		}

	}

	fclose(objFile);

	for (size_t i = 0; i < indPositions.size(); i++) {

		vec3 vecPos;
		vec2 vecTex;
		vec3 vecNorm;

		vecPos = positions[indPositions[i]];
		if (textures.size() > indTextures[i]) {

			vecTex = textures[indTextures[i]];
		}
		else {
			vecTex = vec2(0.0, 0.0);
		}

		if (normals.size() > indNormals[i]) {
			vecNorm = normals[indNormals[i]];
		}
		else {
			vecNorm = vec3(0.0, 0.0, 0.0);
		}

		//push positions
		vertexBuffer.push_back(vecPos.x);
		vertexBuffer.push_back(vecPos.y);
		vertexBuffer.push_back(vecPos.z);

		//push texture
		vertexBuffer.push_back(vecTex.x);
		vertexBuffer.push_back(vecTex.y);

		//push normals
		vertexBuffer.push_back(vecNorm.x);
		vertexBuffer.push_back(vecNorm.y);
		vertexBuffer.push_back(vecNorm.z);

	}

	/* set vertexbuffer + attributes */
	this->vao.bind();

	this->vao.setData(&(vertexBuffer[0]), (int)vertexBuffer.size());
	this->vao.setVertexAttrib(0, 0, 3, 8, 0);
	this->vao.setVertexAttrib(1, 1, 2, 8, 3);
	this->vao.setVertexAttrib(2, 2, 3, 8, 5);


}
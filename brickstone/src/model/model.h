#pragma once
#include <logging/log.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "texture.h"
#include "mesh.h"

namespace bs {

	class Model {

	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType name);

	public:
		Model(const char* path);
		~Model();

		void draw(Shader shader);

	};

}
#pragma once
#include <logging/log.h>
#include <texture/texture.h>
#include <texture/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace bs {

	class Model {

	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Path;
		std::vector<std::string> m_TexturePaths;
		std::vector<Texture> m_Textures;
		
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name);
		Texture textureFromFile(std::string& path);
	public:
		Model(std::string& path);
		~Model();

		void loadModel(std::string& path);

	};

}
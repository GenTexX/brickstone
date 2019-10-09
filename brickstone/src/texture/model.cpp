#include <bspch.h>
#include "model.h"

namespace bs {

	bs::Model::Model(std::string& path) {
		this->loadModel(path);
	}

	bs::Model::~Model()	{
		
	}

	void bs::Model::processNode(aiNode* node, const aiScene* scene) {
		
		for (int i = 0; i < node->mNumMeshes; i++) {
			Mesh mesh = this->processMesh(scene->mMeshes[i], scene);
			this->m_Meshes.push_back(mesh);
		}

		for (int i = 0; i < node->mNumChildren; i++) {
			this->processNode(node->mChildren[i], scene);
		}

	}

	Mesh bs::Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{

		std::vector<vertex> vertices;
		std::vector<int> indices;
		std::vector<Texture> textures;

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex v;
			
			v.position.x = mesh->mVertices[i].x;
			v.position.y = mesh->mVertices[i].y;
			v.position.z = mesh->mVertices[i].z;

			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0]) {

				vec2 vec;

				v.texCoord.x = mesh->mTextureCoords[0][i].x;
				v.texCoord.y = mesh->mTextureCoords[0][i].y;
				
			}
			else {
				v.texCoord = ivec2(0, 0);
			}

			vertices.push_back(v);

		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}

		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMap = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

			textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

		}

		return Mesh(vertices, indices, textures);

	}

	std::vector<Texture> bs::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name)
	{

		std::vector<Texture> textures;

		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{

			aiString fileName;
			mat->GetTexture(type, i, &fileName);
			bool skip = false;

			for (int j = 0; j < m_TexturePaths.size(); j++) {
				if (m_TexturePaths[j] == std::string(fileName.C_Str())) {

					textures.push_back(this->m_Textures[j]);
					skip = true;

				}
			}

			if (!skip) {
				this->m_TexturePaths.push_back(std::string(fileName.C_Str()));
				this->m_Textures.push_back(Texture(this->m_Path.substr(0, this->m_Path.find_last_of('/'))));
				switch (type) {
				case aiTextureType_DIFFUSE:
					this->m_Textures.back().setType(DIFFUSE_MAP);
					break;
				case aiTextureType_SPECULAR:
					this->m_Textures.back().setType(SPECULAR_MAP);
					break;
				default:
					Log::warn("No Valid texturetype {}", type);
					this->m_Textures.back().setType(DIFFUSE_MAP);

				}
			
			}

		}
			
	}

	Texture bs::Model::textureFromFile(std::string& path)
	{
		return Texture();
	}

	void bs::Model::loadModel(std::string& path) {

		this->m_Path = path;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			Log::error("Failed to load: {}", this->m_Path);
		}

		this->processNode(scene->mRootNode, scene);

	}

}
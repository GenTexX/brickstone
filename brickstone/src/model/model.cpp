#include <bspch.h>
#include "model.h"

namespace bs {

	bs::Model::Model(const char* path) {
		this->loadModel(path);
	}

	bs::Model::~Model()	{
		
	}

	void bs::Model::processNode(aiNode* node, const aiScene* scene) {
		
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->m_Meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			this->processNode(node->mChildren[i], scene);
		}

	}

	Mesh bs::Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{

		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex v;
			
			v.position.x = mesh->mVertices[i].x;
			v.position.y = mesh->mVertices[i].y;
			v.position.z = mesh->mVertices[i].z;

			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0]) {

				v.texCoord.x = mesh->mTextureCoords[0][i].x;
				v.texCoord.y = mesh->mTextureCoords[0][i].y;
				
			}
			else {
				v.texCoord = vec2(0, 0);
			}

			vertices.push_back(v);

		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}

		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE_MAP);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, SPECULAR_MAP);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		}

		return Mesh(vertices, indices, textures);

	}

	std::vector<Texture> bs::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType name)
	{

		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture(std::string(str.C_Str()));
			texture.setType(name);
			textures.push_back(texture);

		}
	
		return textures;

	}

	void bs::Model::loadModel(std::string path) {


		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			Log::error("Failed to load: {}", path);
			Log::error("Assimp-Error: {}", importer.GetErrorString());
			return;
		}

		this->m_Directory = path.substr(0, path.find_last_of('/'));

		this->processNode(scene->mRootNode, scene);
		
	}

	void Model::draw(Shader shader) {

		for (unsigned int i = 0; i < m_Meshes.size(); i++)
			this->m_Meshes[i].draw(shader);

	}

}
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

	Mesh* bs::Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{

		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		Material* mat = new Material();

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

			*mat = this->loadMaterial(material);
			

			std::vector<std::string> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE_MAP);
			if (diffuseMaps.size() != 0)
			{
				mat->loadDiffuseMap(diffuseMaps[0]);
			}
			
			std::vector<std::string> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, DIFFUSE_MAP);
			if (specularMaps.size() != 0)
			{
				mat->loadSpecularMap(specularMaps[0]);
			}
			
		}

		return new Mesh(vertices, indices, mat);

	}

	std::vector<std::string> bs::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType name)
	{

		std::vector<std::string> texturePaths;

		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

			aiString str;
			mat->GetTexture(type, i, &str);
			std::string t1 = this->m_Directory + "/" + std::string(str.C_Str());
			texturePaths.push_back(t1);

		}
	
		return texturePaths;

	}

	Material Model::loadMaterial(aiMaterial* mat) {

		aiColor3D color(0.0f, 0.0f, 0.0f);

		mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		vec3 diffuse(color.r, color.g, color.b);
		diffuse *= 0.8f;
		
		//mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
		vec3 ambient(color.r, color.g, color.b);
		ambient *= 1.2f;

		mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
		vec3 specular(color.r, color.g, color.b);


		float shininess;
		mat->Get(AI_MATKEY_SHININESS, shininess);
		shininess /= 10;

		return Material(diffuse, ambient, specular, shininess);

	}

	void bs::Model::loadModel(std::string path) {


		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate/* | aiProcess_FlipUVs*/);
		
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
			this->m_Meshes[i]->draw(shader);

	}

}
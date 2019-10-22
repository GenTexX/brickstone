#include <bspch.h>
#include "terrain.h"

namespace bs {

	Terrain::Terrain(float width, float height, int countWidth, int countHeight, float hardness, float textureScale, float noiseFrequency) {

		this->m_Width = width;
		this->m_Height = height;
		this->m_CountWidth = countWidth;
		this->m_CountHeight = countHeight;
		this->m_Hardness = hardness;
		this->m_TextureScale = textureScale;
		this->m_NoiseFrequency = noiseFrequency;

		this->m_Noise.SetNoiseType(FastNoise::PerlinFractal);
		this->m_Noise.SetFrequency(m_NoiseFrequency);
		
		Material* mat = new Material(vec3(0.2f, 0.2f, 0.2f), vec3(0.4f, 0.4f, 0.4f), vec3(0.1f, 0.1f, 0.1f), 32.0f);
		mat->loadDiffuseMap("src/res/grass.png");
		this->m_Mesh.m_Material = mat;
		
		this->load();

	}

	Terrain::~Terrain() {}

	void Terrain::draw(Shader shader) {

		this->m_Mesh.draw(shader);

	}

	void Terrain::load() {

		this->m_Noise.SetFrequency(this->m_NoiseFrequency);

		float resolutionW = (this->m_Width) / (this->m_CountWidth);
		float resolutionH = (this->m_Height) / (this->m_CountHeight);

		this->m_Mesh.m_Vertices.clear();
		this->m_Mesh.m_Indices.clear();

		std::vector<vec3> grid;
		for (size_t i = 0; i < m_CountHeight; i++)
		{
			for (size_t j = 0; j < m_CountWidth; j++) {
				grid.push_back(vec3(resolutionW * (j - (m_CountWidth-1) * 0.5f), m_Noise.GetNoise((float)i * (32.0f / (float)m_CountWidth), (float)j * (32.0f / m_CountHeight)) * (this->m_Hardness / 10.0f), resolutionH * (i - (m_CountHeight-1) * 0.5f)));
			}
		}

		for (size_t i = 0; i < (size_t)m_CountHeight - 1; i++)
		{

			for (size_t j = 0; j < (size_t)m_CountWidth - 1; j++)
			{
				vec3 pos1, pos2, pos3, pos4;

				pos1 = grid[j + m_CountWidth * i];
				pos2 = grid[j + m_CountWidth * (i + 1)];
				pos3 = grid[(j + 1) + m_CountWidth * i];
				pos4 = grid[(j + 1) + m_CountWidth * (i + 1)];

				vertex v1, v2, v3, v4, v5, v6;

				v1.position = pos1;

				v2.position = pos2;

				v3.position = pos3;

				v4.position = pos3;

				v5.position = pos2;

				v6.position = pos4;

				float textureCoordinateY = (i / (float)this->m_CountHeight) * m_TextureScale;
				float textureCoordinateX = (j / (float)this->m_CountWidth) * m_TextureScale;

				v1.texCoord = vec2(textureCoordinateX, textureCoordinateY);
				v2.texCoord = vec2(textureCoordinateX, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);
				v3.texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY);
				v4.texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY);
				v5.texCoord = vec2(textureCoordinateX, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);
				v6.texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);

				vec3 normal1 = 1 * vec3::cross((v1.position - v2.position), (v2.position - v3.position)).normalized();
				vec3 normal2 = 1 * vec3::cross((v4.position - v5.position), (v4.position - v6.position)).normalized();


				v1.normal = normal1;
				v2.normal = normal1;
				v3.normal = normal1;

				v4.normal = normal2;
				v5.normal = normal2;
				v6.normal = normal2;

				this->m_Mesh.m_Vertices.push_back(v1);
				this->m_Mesh.m_Vertices.push_back(v2);
				this->m_Mesh.m_Vertices.push_back(v3);
				this->m_Mesh.m_Vertices.push_back(v4);
				this->m_Mesh.m_Vertices.push_back(v5);
				this->m_Mesh.m_Vertices.push_back(v6);

				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 6);
				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 5);
				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 4);
				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 3);
				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 2);
				this->m_Mesh.m_Indices.push_back((int)this->m_Mesh.m_Vertices.size() - 1);

			}
		}

		this->m_Mesh.setupMesh();


	}

	void Terrain::loadTextureCoordinates() {

		int vertCount = 0;

		for (size_t i = 0; i < (size_t)m_CountHeight - 1; i++)
		{
			for (size_t j = 0; j < (size_t)m_CountWidth - 1; j++)
			{


				float textureCoordinateY = (i / (float)this->m_CountHeight) * (m_TextureScale);
				float textureCoordinateX = (j / (float)this->m_CountWidth) * (m_TextureScale );

				this->m_Mesh.m_Vertices[vertCount].texCoord = vec2(textureCoordinateX, textureCoordinateY);
				this->m_Mesh.m_Vertices[vertCount + 1].texCoord = vec2(textureCoordinateX, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);
				this->m_Mesh.m_Vertices[vertCount + 2].texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY);
				this->m_Mesh.m_Vertices[vertCount + 3].texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY);
				this->m_Mesh.m_Vertices[vertCount + 4].texCoord = vec2(textureCoordinateX, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);
				this->m_Mesh.m_Vertices[vertCount + 5].texCoord = vec2(textureCoordinateX + (1.0f / m_CountWidth) * m_TextureScale, textureCoordinateY + (1.0f / m_CountHeight) * m_TextureScale);

				vertCount += 6;

			}
		}


		this->m_Mesh.setupMesh();

	}

}
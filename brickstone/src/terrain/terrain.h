#pragma once
#include <shader/shader.h>
#include <model/mesh.h>
#include "noiseMap.h"
#include "FastNoise.h"

namespace bs {

	class Terrain {

	private:
		Mesh m_Mesh;
		FastNoise m_Noise;

	public:
		float m_Width;
		float m_Height;
		int m_CountWidth;
		int m_CountHeight;
		float m_Hardness;
		float m_TextureScale;

		Terrain(float width, float height, int countWidth, int countHeight, float hardness, float textureScale = 1.0f);
		~Terrain();

		void draw(Shader shader);
		void load();
		void loadTextureCoordinates();

	};

}
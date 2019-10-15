#include "bspch.h"
#include "noiseMap.h"

bs::noiseMap::noiseMap(int width, int height, int octaves)
	: m_Width(width), m_Height(height), m_Octaves(octaves), m_Seed(nullptr), m_Noise(nullptr) {

	this->m_Seed = new float[(size_t)width * (size_t)height];
	this->m_Noise = new float[(size_t)width * (size_t)height];

	for (size_t i = 0; i < (size_t)width * (size_t)height; i++)	{

		this->m_Seed[i] = (float)rand() / (float)(RAND_MAX);

	}


	for (size_t x = 0; x < (size_t)this->m_Width; x++) {

		for (size_t y = 0; y < (size_t)this->m_Height; y++) {

			float noise = 0.0f;
			float scale = 1.0f;
			float scaleAcc = 0.0f;

			for (size_t i = 0; i < this->m_Octaves; i++) {

				int pitchX = this->m_Width >> i;
				int pitchY = this->m_Height >> i;

				if (pitchX == 0 || pitchY == 0) break;

				int sampleX1 = (x / pitchX) * pitchX;
				int sampleX2 = (sampleX1 + pitchX) % this->m_Width;

				int sampleY1 = (y / pitchY) * pitchY;
				int sampleY2 = (sampleY1 + pitchY) % this->m_Height;

				float blendX = (float)(x - sampleX1) / (float)pitchX;
				float blendY = (float)(y - sampleY1) / (float)pitchY;

				float sampleT = (1.0f - blendX) * this->m_Seed[sampleY1 * this->m_Width + sampleX1] + blendX * this->m_Seed[sampleY1 * this->m_Width + sampleX2];
				
				float sampleB = (1.0f - blendX) * this->m_Seed[sampleY2 * this->m_Width + sampleX1] + blendX * this->m_Seed[sampleY2 * this->m_Width + sampleX2];

				noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
				scaleAcc += scale;
				scale = scale / 1.6f;

			}

			this->m_Noise[y * this->m_Width + x] = noise / scaleAcc;

		}

	}

}

bs::noiseMap::~noiseMap() {

	delete[] this->m_Seed;
	delete[] this->m_Noise;

}

float* bs::noiseMap::getNoiseMap()
{
	return this->m_Noise;
}

float bs::noiseMap::noise(float x, float y)
{
	int refX1 = (int)x;
	int refX2 = refX1 + 1;

	int refY1 = (int)y;
	int refY2 = refY1 + 1;

	float val1, val2, val3, val4;
	
	val1 = this->m_Seed[refX1 + m_Width * refY1];
	val2 = this->m_Seed[refX2 + m_Width * refY1];
	val3 = this->m_Seed[refX1 + m_Width * refY2];
	val4 = this->m_Seed[refX2 + m_Width * refY2];

	float p1 = val1 * (1.0f - floor(x)) + val2 * floor(x);
	float p2 = val3 * (1.0f - floor(x)) + val4 * floor(x);

	return p1 * (1.0f - floor(y)) + p2 * floor(y);
}

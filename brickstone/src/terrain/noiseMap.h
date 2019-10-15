#pragma once

namespace bs {

	struct noiseMap {

		int m_Width;
		int m_Height;
		int m_Octaves;
		float* m_Seed;
		float* m_Noise;

		noiseMap(int width = 0, int height = 0, int octaves = 0);
		~noiseMap();

		float* getNoiseMap();
		float noise(float x, float y);

	};

}
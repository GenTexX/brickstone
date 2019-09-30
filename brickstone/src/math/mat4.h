#pragma once

/*
		 C0   C1   C2   C3
	   |-------------------|
	R0 | 0  | 4  | 8  | 12 |
	R1 | 1  | 5  | 9  | 13 |
	R2 | 2  | 6  | 10 | 14 |
	R3 | 3  | 7  | 11 | 15 |
	   |-------------------|
		
		ACCESS TO ELEMENT
		elements[Cx + Rx * 4]

*/

namespace bs {

	struct mat4 {

	public:

		float elements[16];
		 
		mat4();
		mat4(float diagonal);

		mat4& multiply(const mat4& other);
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		static mat4 identity();

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspect, float near, float far);
		
		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

	};

}
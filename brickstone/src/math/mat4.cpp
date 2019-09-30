#include "maths.h"
#include "maths_func.h"
#include <math.h>

namespace bs {

	mat4::mat4() {

		/*init matrix*/
		for (int i = 0; i < 16; i++) {
			this->elements[i] = 0.0f;
		}

	}

	mat4::mat4(float diagonal) {

		/*init matrix + diagonal*/
		for (int i = 0; i < 16; i++) {
			this->elements[i] = 0.0f;
		}

		/*set diagonal*/
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;

	}

	mat4 mat4::identity() {

		/*init matrix + diagonal = 1.0f*/
		mat4 result(1.0f);
		return result;

	}

	mat4& mat4::multiply(const mat4& other) {

		float n[4 * 4];

		/*multiply matrix with other*/
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float val = 0.0f;
				for (int e = 0; e < 4; e++) {
					val += this->elements[x + e * 4] * other.elements[e + y * 4];
				}
				n[x + y * 4] = val;
			}
		}

		for (size_t i = 0; i < 16; i++) {
			this->elements[i] = n[i];
		}

		return *this;

	}

	mat4& mat4::operator*=(const mat4& other) {

		/*multiplay matrix with other*/
		this->multiply(other);
		return *this;

	}

	mat4 operator*(mat4 left, const mat4& right) {

		/*multiplay matrix left with right*/
		return left.multiply(right);

	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {

		/*generate orthigraphic matrix*/
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = ((2.0f) / (right - left));
		result.elements[1 + 1 * 4] = ((2.0f) / (top - bottom));
		result.elements[2 + 2 * 4] = (2.0f) / (near - far);
		result.elements[0 + 3 * 4] = ((right + left)) / (left - right);
		result.elements[1 + 3 * 4] = ((top + bottom)) / (bottom - top);
		result.elements[2 + 3 * 4] = ((far + near)) / (far - near);

		return result;
	} 

	mat4 mat4::perspective(float fov, float aspect, float near, float far) {
		
		/*generate perspective matrix*/
		mat4 result(0.0f);

		float q = 1.0f / tan(toRad(0.5f * fov));
		float a = q / aspect;
		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;

	}

	mat4 mat4::translation(const vec3& translation) {

		/*generate translation matrix*/
		mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;	//translate x-axis
		result.elements[1 + 3 * 4] = translation.y;	//translate y-axis
		result.elements[2 + 3 * 4] = translation.z;	//translate z-axis

		return result;

	}

	mat4 mat4::scale(const vec3& scale) {

		/*generate scale matrix*/
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;	//scale x-axis
		result.elements[1 + 1 * 4] = scale.y;	//scale y-axis
		result.elements[2 + 2 * 4] = scale.z;	//scale z-axis

		return result;

	}

	mat4 mat4::rotation(float angle, const vec3& axis) {

		/*generate rotation matrix*/
		mat4 result(1.0f);

		float radAngle = toRad(angle);		//angle in radians
		float s = (float) sin(radAngle);	//sinus		angle
		float c = (float) cos(radAngle);	//cosinus	angle
		float nc = 1.0f - c;				//not cosinus = 1 - cosinus

		result.elements[0 + 0 * 4] = axis.x * nc + c;
		result.elements[1 + 0 * 4] = axis.x * axis.y * nc + axis.z * s;
		result.elements[2 + 0 * 4] = axis.x * axis.z * nc - axis.y * s;

		result.elements[0 + 1 * 4] = axis.x * axis.y * nc - axis.z * s;
		result.elements[1 + 1 * 4] = axis.y * nc + c;
		result.elements[2 + 1 * 4] = axis.y * axis.z * nc + axis.x * s;
		
		result.elements[0 + 2 * 4] = axis.x * axis.z * nc + axis.y * s;
		result.elements[1 + 2 * 4] = axis.y * axis.z * nc - axis.x * s;
		result.elements[2 + 2 * 4] = axis.z * nc + c;

		return result;

	}

}
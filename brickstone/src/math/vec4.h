#pragma once

#include <math.h>
#include <string>

namespace bs {

	struct vec4 {		

	public:

		static const vec4 one, zero;
		float x, y, z, w;

		vec4();
		vec4(const float &x, const float &y, const float &z, const float &w);
		~vec4();

		float magnitude();
		float sqrMagnitude();
		vec4 normalized();
		bool equals(vec4& other);

		//calculation
		vec4& add(const vec4& other);
		vec4& sub(const vec4& other);
		vec4& mult(const vec4& other);
		vec4& div(const vec4& other);

		vec4& add(const float& other);
		vec4& sub(const float& other);
		vec4& mult(const float& other);
		vec4& div(const float& other);
		
		//operators
		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator/=(const vec4& other);

		vec4& operator+=(const float& other);
		vec4& operator-=(const float& other);
		vec4& operator*=(const float& other);
		vec4& operator/=(const float& other);

		bool operator==(const vec4& other);
		bool operator!=(const vec4& other);
		bool operator>(vec4& other);
		bool operator<(vec4& other);
		bool operator>=(vec4& other);
		bool operator<=(vec4& other);

		friend vec4 operator+(vec4 left, const vec4& right);
		friend vec4 operator-(vec4 left, const vec4& right);
		friend vec4 operator*(vec4 left, const vec4& right);
		friend vec4 operator/(vec4 left, const vec4& right);

		friend vec4 operator+(vec4 left, const float& right);
		friend vec4 operator-(vec4 left, const float& right);
		friend vec4 operator*(vec4 left, const float& right);
		friend vec4 operator/(vec4 left, const float& right);

		friend vec4 operator+(const float& left, vec4 right);
		friend vec4 operator*(const float& left, vec4 right);

		friend std::ostream& operator<<(std::ostream& stream, vec4& vector);

		static float dot(const vec4& left, const vec4& right);
		static float distance(const vec4& left, const vec4& right);
		static float sqrDistance(const vec4& left, const vec4& right);
		static vec4 lerp(const vec4& left, const vec4& right, const float& t);

		std::string toString();

	};

}
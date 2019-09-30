#pragma once

#include <math.h>
#include <string>

namespace bs {

	struct vec2 {

	public:

		float x, y;

		vec2();
		vec2(const float& x, const float& y);
		~vec2();

		static const vec2 up, down, right, left, one, zero;

		float magnitude();
		float sqrMagnitude();
		vec2 normalized();
		bool equals(vec2& other);

		//calculation
		vec2& add(const vec2& other);
		vec2& sub(const vec2& other);
		vec2& mult(const vec2& other);
		vec2& div(const vec2& other);

		vec2& add(const float& other);
		vec2& sub(const float& other);
		vec2& mult(const float& other);
		vec2& div(const float& other);

		//operators
		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		vec2& operator+=(const float& other);
		vec2& operator-=(const float& other);
		vec2& operator*=(const float& other);
		vec2& operator/=(const float& other);

		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);
		bool operator>(vec2& other);
		bool operator<(vec2& other);
		bool operator>=(vec2& other);
		bool operator<=(vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		friend vec2 operator+(vec2 left, const float& right);
		friend vec2 operator-(vec2 left, const float& right);
		friend vec2 operator*(vec2 left, const float& right);
		friend vec2 operator/(vec2 left, const float& right);

		friend vec2 operator+(const float&  left, vec2 right);
		friend vec2 operator*(const float&  left, vec2 right);

		friend std::ostream& operator<<(std::ostream& stream, vec2& vector);

		static float dot(const vec2& left, const vec2& right);
		static float distance(const vec2& left, const vec2& right);
		static float sqrDistance(const vec2& left, const vec2& right);
		static vec2 lerp(const vec2& left, const vec2& right, const float& t);

		std::string toString();

	};

}
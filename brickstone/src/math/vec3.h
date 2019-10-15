#pragma once

#include <math.h>
#include <string>


namespace bs {

	struct vec3 {

	public:

		float x, y, z;

		vec3();
		vec3(const float &x, const float &y, const float &z);
		~vec3();

		static const vec3 up, down, right, left, back, forward, one, zero;


		float magnitude();
		float sqrMagnitude();
		vec3 normalized();
		bool equals(vec3& other);

		//calculation
		vec3& add(const vec3& other);
		vec3& sub(const vec3& other);
		vec3& mult(const vec3& other);  
		vec3& div(const vec3& other);

		vec3& add(const float& other);
		vec3& sub(const float& other);
		vec3& mult(const float& other);
		vec3& div(const float& other);
		
		//operators
		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		vec3& operator+=(const float& other);
		vec3& operator-=(const float& other);
		vec3& operator*=(const float& other);
		vec3& operator/=(const float& other);

		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);
		bool operator>(vec3& other);
		bool operator<(vec3& other);
		bool operator>=(vec3& other);
		bool operator<=(vec3& other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		friend vec3 operator+(vec3 left, const float& right);
		friend vec3 operator-(vec3 left, const float& right);
		friend vec3 operator*(vec3 left, const float& right);
		friend vec3 operator/(vec3 left, const float& right);
				  
		friend vec3 operator+(const float&  left, vec3 right);
		friend vec3 operator*(const float&  left, vec3 right);

		friend std::ostream& operator<<(std::ostream& stream, vec3& vector);

		static float dot(const vec3& left, const vec3& right);
		static vec3 cross(const vec3& left, const vec3& right);
		static float distance(const vec3& left, const vec3& right);
		static float sqrDistance(const vec3& left, const vec3& right);
		static vec3 lerp(const vec3& left, const vec3& right, const float& t);

		std::string toString();

	};

}
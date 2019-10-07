#pragma once

#include <math.h>
#include <string>

namespace bs {

	struct ivec2 {

	public:

		int x, y;

		ivec2();
		ivec2(const int& x, const int& y);
		~ivec2();

		static const ivec2 up, down, right, left, one, zero;

		float magnitude();
		float sqrMagnitude();
		ivec2 normalized();
		bool equals(ivec2& other);

		//calculation
		ivec2& add(const ivec2& other);
		ivec2& sub(const ivec2& other);
		ivec2& mult(const ivec2& other);
		ivec2& div(const ivec2& other);
		
		ivec2& add(const int& other);
		ivec2& sub(const int& other);
		ivec2& mult(const int& other);
		ivec2& div(const int& other);

		//operators
		ivec2& operator+=(const ivec2& other);
		ivec2& operator-=(const ivec2& other);
		ivec2& operator*=(const ivec2& other);
		ivec2& operator/=(const ivec2& other);
		
		ivec2& operator+=(const int& other);
		ivec2& operator-=(const int& other);
		ivec2& operator*=(const int& other);
		ivec2& operator/=(const int& other);

		bool operator==(const ivec2& other);
		bool operator!=(const ivec2& other);
		bool operator>(ivec2& other);
		bool operator<(ivec2& other);
		bool operator>=(ivec2& other);
		bool operator<=(ivec2& other);

		friend ivec2 operator+(ivec2 left, const ivec2& right);
		friend ivec2 operator-(ivec2 left, const ivec2& right);
		friend ivec2 operator*(ivec2 left, const ivec2& right);
		friend ivec2 operator/(ivec2 left, const ivec2& right);
			   
		friend ivec2 operator+(ivec2 left, const int& right);
		friend ivec2 operator-(ivec2 left, const int& right);
		friend ivec2 operator*(ivec2 left, const int& right);
		friend ivec2 operator/(ivec2 left, const int& right);

		friend ivec2 operator+(const int& left, ivec2 right);
		friend ivec2 operator*(const int& left, ivec2 right);

		friend std::ostream& operator<<(std::ostream& stream, ivec2& vector);

		static float dot(const ivec2& left, const ivec2& right);
		static float distance(const ivec2& left, const ivec2& right);
		static float sqrDistance(const ivec2& left, const ivec2& right);
		static ivec2 lerp(const ivec2& left, const ivec2& right, const float& t);

		std::string toString();

	};

}
#include <bspch.h>
#include "ivec2.h"

namespace bs {

	const ivec2 ivec2::up(0, 1);
	const ivec2 ivec2::down(0, -1);
	const ivec2 ivec2::right(1, 0);
	const ivec2 ivec2::left(-1, 0);
	const ivec2 ivec2::one(1, 1);
	const ivec2 ivec2::zero(0, 0);

	ivec2::ivec2() : x(0), y(0) {

	}

	ivec2::ivec2(const int& x, const int& y) : x(x), y(y) {

	}

	ivec2::~ivec2() {

	}



	float ivec2::magnitude() {

		return (float)sqrt(this->x * this->x + this->y * this->y);

	}

	int ivec2::sqrMagnitude() {

		return this->x * this->x + this->y * this->y;

	}

	bool ivec2::equals(ivec2& other) {

		return *this == other;

	}



	ivec2& ivec2::add(const ivec2& other) {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	ivec2& ivec2::sub(const ivec2& other) {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	ivec2& ivec2::mult(const ivec2& other) {
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	ivec2& ivec2::div(const ivec2& other) {
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	ivec2& ivec2::add(const int& other) {

		this->x += other;
		this->y += other;

		return *this;

	}

	ivec2& ivec2::sub(const int& other) {

		this->x -= other;
		this->y -= other;

		return *this;

	}

	ivec2& ivec2::mult(const int& other) {

		this->x *= other;
		this->y *= other;

		return *this;

	}

	ivec2& ivec2::div(const int& other) {

		this->x /= other;
		this->y /= other;

		return *this;

	}



	ivec2& ivec2::operator+=(const ivec2& other) {
		return this->add(other);
	}

	ivec2& ivec2::operator-=(const ivec2& other) {
		return this->sub(other);
	}

	ivec2& ivec2::operator*=(const ivec2& other) {
		return this->mult(other);
	}

	ivec2& ivec2::operator/=(const ivec2& other) {
		return this->div(other);
	}

	ivec2& ivec2::operator+=(const int& other) {

		return this->add(other);

	}

	ivec2& ivec2::operator-=(const int& other) {

		return this->sub(other);

	}

	ivec2& ivec2::operator*=(const int& other) {

		return this->mult(other);

	}

	ivec2& ivec2::operator/=(const int& other) {

		return this->div(other);

	}



	bool ivec2::operator==(const ivec2& other) {
		return (this->x == other.x && this->y == other.y);
	}

	bool ivec2::operator!=(const ivec2& other) {
		return !(this->x == other.x && this->y == other.y);
	}

	bool ivec2::operator>(ivec2& other) {

		return (this->sqrMagnitude() > other.sqrMagnitude());

	}

	bool ivec2::operator<(ivec2& other) {

		return (this->sqrMagnitude() < other.sqrMagnitude());

	}

	bool ivec2::operator>=(ivec2& other) {

		return (this->sqrMagnitude() >= other.sqrMagnitude());

	}

	bool ivec2::operator<=(ivec2& other) {

		return (this->sqrMagnitude() <= other.sqrMagnitude());

	}



	ivec2 operator+(ivec2 left, const ivec2& right) {

		return left.add(right);

	}

	ivec2 operator-(ivec2 left, const ivec2& right) {

		return left.sub(right);

	}

	ivec2 operator*(ivec2 left, const ivec2& right) {

		return left.mult(right);;

	}

	ivec2 operator/(ivec2 left, const ivec2& right) {

		return left.div(right);;

	}

	ivec2 operator+(ivec2 left, const int& right) {

		left.x += right;
		left.y += right;
		return left;

	}

	ivec2 operator-(ivec2 left, const int& right) {

		left.x -= right;
		left.y -= right;
		return left;

	}

	ivec2 operator*(ivec2 left, const int& right) {

		left.x *= right;
		left.y *= right;
		return left;

	}

	ivec2 operator/(ivec2 left, const int& right) {

		left.x /= right;
		left.y /= right;
		return left;

	}

	ivec2 operator+(const int& left, ivec2 right) {

		right.x += left;
		right.y += left;
		return right;

	}

	ivec2 operator*(const int& left, ivec2 right) {

		right.x *= left;
		right.y *= left;
		return right;

	}



	std::ostream& operator<<(std::ostream& stream, ivec2& vector) {

		stream << vector.toString();
		return stream;

	}

	float ivec2::distance(const ivec2& left, const ivec2& right) {

		return (left - right).magnitude();

	}

	int ivec2::sqrDistance(const ivec2& left, const ivec2& right) {

		return (left - right).sqrMagnitude();

	}

	ivec2 ivec2::lerp(const ivec2& left, const ivec2& right, const int& t) {

		return ((right - left) * t) + left;

	}



	std::string ivec2::toString() {

		return "(" + std::to_string(this->x) + " | " + std::to_string(this->y) + ")";

	}


}
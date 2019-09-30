#include <bspch.h>
#include "Vec2.h"

namespace bs {

	const vec2 vec2::up(0.0f, 1.0f);
	const vec2 vec2::down(0.0f, -1.0f);
	const vec2 vec2::right(1.0f, 0.0f);
	const vec2 vec2::left(-1.0f, 0.0f);
	const vec2 vec2::one(1.0f, 1.0f);
	const vec2 vec2::zero(0.0f, 0.0f);

	vec2::vec2() : x(0.0f), y(0.0f) {

	}

	vec2::vec2(const float &x, const float &y) : x(x), y(y) {

	}

	vec2::~vec2() {

	}



	float vec2::magnitude() {

		return (float) sqrt(this->x * this->x + this->y * this->y);

	}

	float vec2::sqrMagnitude() {

		return this->x * this->x + this->y * this->y;

	}

	vec2 vec2::normalized() {

		return *this / this->magnitude();

	}

	bool vec2::equals(vec2& other) {

		return *this == other;

	}



	vec2& vec2::add(const vec2& other) {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	vec2& vec2::sub(const vec2& other) {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	vec2& vec2::mult(const vec2& other) {
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	vec2& vec2::div(const vec2& other) {
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	vec2& vec2::add(const float& other) {
		
		this->x += other;
		this->y += other;

		return *this;

	}

	vec2& vec2::sub(const float& other) {

		this->x -= other;
		this->y -= other;

		return *this;

	}

	vec2& vec2::mult(const float& other) {

		this->x *= other;
		this->y *= other;

		return *this;

	}

	vec2& vec2::div(const float& other) {

		this->x /= other;
		this->y /= other;

		return *this;

	}



	vec2& vec2::operator+=(const vec2& other) {
		return this->add(other);
	}

	vec2& vec2::operator-=(const vec2& other) {
		return this->sub(other);
	}

	vec2& vec2::operator*=(const vec2& other) {
		return this->mult(other);
	}

	vec2& vec2::operator/=(const vec2& other) {
		return this->div(other);
	}

	vec2& vec2::operator+=(const float& other) {

		return this->add(other);

	}

	vec2& vec2::operator-=(const float& other) {

		return this->sub(other);

	}

	vec2& vec2::operator*=(const float& other) {

		return this->mult(other);

	}

	vec2& vec2::operator/=(const float& other) {

		return this->div(other);

	}



	bool vec2::operator==(const vec2& other) {
		return (this->x == other.x && this->y == other.y);
	}

	bool vec2::operator!=(const vec2& other) {
		return !(this->x == other.x && this->y == other.y);
	}

	bool vec2::operator>(vec2& other) {

		return (this->sqrMagnitude() > other.sqrMagnitude());

	}

	bool vec2::operator<(vec2& other) {

		return (this->sqrMagnitude() < other.sqrMagnitude());

	}

	bool vec2::operator>=(vec2& other) {

		return (this->sqrMagnitude() >= other.sqrMagnitude());

	}

	bool vec2::operator<=(vec2& other) {

		return (this->sqrMagnitude() <= other.sqrMagnitude());

	}



	vec2 operator+(vec2 left, const vec2& right) {

		return left.add(right);

	}

	vec2 operator-(vec2 left, const vec2& right) {

		return left.sub(right);

	}

	vec2 operator*(vec2 left, const vec2& right) {

		return left.mult(right);;

	}

	vec2 operator/(vec2 left, const vec2& right) {

		return left.div(right);;

	}

	vec2 operator+(vec2 left, const float& right) {

		left.x += right;
		left.y += right;
		return left;

	}

	vec2 operator-(vec2 left, const float& right) {

		left.x -= right;
		left.y -= right;
		return left;

	}

	vec2 operator*(vec2 left, const float& right) {

		left.x *= right;
		left.y *= right;
		return left;

	}

	vec2 operator/(vec2 left, const float& right) {

		left.x /= right;
		left.y /= right;
		return left;

	}

	vec2 operator+(const float&  left, vec2 right) {

		right.x += left;
		right.y += left;
		return right;

	}

	vec2 operator*(const float&  left, vec2 right) {

		right.x *= left;
		right.y *= left;
		return right;

	}



	std::ostream& operator<<(std::ostream& stream, vec2& vector) {

		stream << vector.toString();
		return stream;

	}



	float vec2::dot(const vec2& left, const vec2& right) {

		return left.x * right.x + left.y * right.y;

	}

	float vec2::distance(const vec2& left, const vec2& right) {

		return (left-right).magnitude();

	}

	float vec2::sqrDistance(const vec2& left, const vec2& right) {

		return (left - right).sqrMagnitude();

	}

	vec2 vec2::lerp(const vec2& left, const vec2& right, const float& t) {

		return ((right - left) * t) + left;

	}



	std::string vec2::toString() {

		return "(" + std::to_string(this->x) + " | " + std::to_string(this->y) + ")";

	}


}
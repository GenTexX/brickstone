#include <bspch.h>
#include "Vec3.h"

namespace bs {

	const vec3 vec3::up(0.0f, 1.0f, 0.0f);
	const vec3 vec3::down(0.0f, -1.0f, 0.0f);
	const vec3 vec3::right(1.0f, 0.0f, 0.0f);
	const vec3 vec3::left(-1.0f, 0.0f, 0.0f);
	const vec3 vec3::back(0.0f, 0.0f, -1.0f);
	const vec3 vec3::forward(0.0f, 0.0f, 1.0f);
	const vec3 vec3::one(1.0f, 1.0f, 1.0f);
	const vec3 vec3::zero(0.0f, 0.0f, 0.0f);

	vec3::vec3(const float &x, const float &y, const float &z) : x(x), y(y), z(z) {


	}

	vec3::vec3() : x(0), y(0), z(0) {

	}

	vec3::~vec3() {

	}



	float vec3::magnitude() {

		return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

	}

	float vec3::sqrMagnitude() {

		return (float) (this->x * this->x + this->y * this->y + this->z * this->z);


	}

	vec3 vec3::normalized() {

		return *this /= this->magnitude();

	}

	bool vec3::equals(vec3& other) {

		return *this == other;

	}

	

	vec3& vec3::add(const vec3& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	vec3& vec3::sub(const vec3& other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	vec3& vec3::mult(const vec3& other) {
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;

		return *this;
	}

	vec3& vec3::div(const vec3& other) {
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;

		return *this;
	}

	vec3& vec3::add(const float& other) {

		this->x += other;
		this->y += other;
		this->z += other;

		return *this;

	}

	vec3& vec3::sub(const float& other) {

		this->x -= other;
		this->y -= other;
		this->z -= other;

		return *this;

	}

	vec3& vec3::mult(const float& other) {

		this->x *= other;
		this->y *= other;
		this->z *= other;

		return *this;

	}

	vec3& vec3::div(const float& other) {

		this->x /= other;
		this->y /= other;
		this->z /= other;

		return *this;

	}



	vec3& vec3::operator+=(const vec3& other) {
		return this->add(other);
	}

	vec3& vec3::operator-=(const vec3& other) {
		return this->sub(other);
	}

	vec3& vec3::operator*=(const vec3& other) {
		return this->mult(other);
	}

	vec3& vec3::operator/=(const vec3& other) {
		return this->div(other);
	}

	vec3& vec3::operator+=(const float& other) {

		return this->add(other);

	}

	vec3& vec3::operator-=(const float& other) {

		return this->sub(other);

	}

	vec3& vec3::operator*=(const float& other) {

		return this->mult(other);

	}

	vec3& vec3::operator/=(const float& other) {

		return this->div(other);

	}



	bool vec3::operator==(const vec3& other) {
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	bool vec3::operator!=(const vec3& other) {
		return !(this->x == other.x && this->y == other.y && this->z == other.z);
	}

	bool vec3::operator>(vec3& other) {

		return (this->sqrMagnitude() > other.sqrMagnitude());

	}

	bool vec3::operator<(vec3& other) {

		return (this->sqrMagnitude() < other.sqrMagnitude());

	}

	bool vec3::operator>=(vec3& other) {

		return (this->sqrMagnitude() >= other.sqrMagnitude());

	}

	bool vec3::operator<=(vec3& other) {

		return (this->sqrMagnitude() <= other.sqrMagnitude());

	}



	vec3 operator+(vec3 left, const vec3& right) {


		return left.add(right);

	}

	vec3 operator-(vec3 left, const vec3& right) {


		return left.sub(right);

	}

	vec3 operator*(vec3 left, const vec3& right) {

		return left.mult(right);;

	}

	vec3 operator/(vec3 left, const vec3& right) {

		return left.div(right);;

	}

	vec3 operator+(vec3 left, const float& right) {

		left.add(right);
		return left;

	}

	vec3 operator-(vec3 left, const float& right) {

		left.sub(right);
		return left;

	}

	vec3 operator*(vec3 left, const float& right) {

		left.mult(right);
		return left;

	}

	vec3 operator/(vec3 left, const float& right) {

		left.div(right);
		return left;

	}

	vec3 operator+(const float&  left, vec3 right) {

		right.add(left);
		return right;

	}

	vec3 operator*(const float&  left, vec3 right) {

		right.mult(left);
		return right;

	}



	std::ostream& operator<<(std::ostream& stream, vec3& vector) {

		stream << vector.toString();
		return stream;

	}



	float vec3::dot(const vec3& left, const vec3& right) {

		return left.x * right.x + left.y * right.y + left.z * left.z;

	}

	vec3 vec3::cross(const vec3& left, const vec3& right) {
		return vec3(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
	}

	float vec3::distance(const vec3& left, const vec3& right) {

		return (left - right).magnitude();

	}

	float vec3::sqrDistance(const vec3& left, const vec3& right) {

		return (left - right).sqrMagnitude();

	}

	vec3 vec3::lerp(const vec3& left, const vec3& right, const float& t) {

		return ((right - left) * t) + left;

	}



	std::string vec3::toString() {

		return "(" + std::to_string(this->x) + " | " + std::to_string(this->y) + " | " + std::to_string(this->z) + ")";

	}


}
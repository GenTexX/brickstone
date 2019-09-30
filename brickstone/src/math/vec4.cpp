#include "Vec4.h"

namespace bs {

	const vec4 vec4::one(1.0f, 1.0f, 1.0f, 1.0f);
	const vec4 vec4::zero(0.0f, 0.0f, 0.0f, 0.0f);

	vec4::vec4( const float &x, const float &y, const float &z, const float &w) : x(x), y(y), z(z), w(w) {

	}

	vec4::vec4() : x(0), y(0), z(0), w(0) {

	}

	vec4::~vec4() {



	}

	

	float vec4::magnitude() {

		return (float)sqrt(this->x * this->x + this->y * this->y);

	}

	float vec4::sqrMagnitude() {

		return (float)(this->x * this->x + this->y * this->y);

	}

	vec4 vec4::normalized() {

		return *this / this->magnitude();

	}

	bool vec4::equals(vec4& other) {

		return *this == other;

	}



	vec4& vec4::add(const vec4& other) {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	vec4& vec4::sub(const vec4& other) {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	vec4& vec4::mult(const vec4& other) {
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	vec4& vec4::div(const vec4& other) {
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	vec4& vec4::add(const float& other) {

		this->x += other;
		this->y += other;
		this->z += other;
		this->w += other;

		return *this;

	}

	vec4& vec4::sub(const float& other) {

		this->x -= other;
		this->y -= other;
		this->z -= other;
		this->w -= other;

		return *this;

	}

	vec4& vec4::mult(const float& other) {

		this->x *= other;
		this->y *= other;
		this->z *= other;
		this->w *= other;

		return *this;

	}

	vec4& vec4::div(const float& other) {

		this->x /= other;
		this->y /= other;
		this->z /= other;
		this->w /= other;

		return *this;

	}



	vec4& vec4::operator+=(const vec4& other) {
		return this->add(other);
	}

	vec4& vec4::operator-=(const vec4& other) {
		return this->sub(other);
	}

	vec4& vec4::operator*=(const vec4& other) {
		return this->mult(other);
	}

	vec4& vec4::operator/=(const vec4& other) {
		return this->div(other);
	}

	vec4& vec4::operator+=(const float& other) {

		return this->add(other);

	}

	vec4& vec4::operator-=(const float& other) {

		return this->sub(other);

	}

	vec4& vec4::operator*=(const float& other) {

		return this->mult(other);

	}

	vec4& vec4::operator/=(const float& other) {

		return this->div(other);

	}



	bool vec4::operator==(const vec4& other) {
		return (this->x == other.x && this->y == other.y);
	}

	bool vec4::operator!=(const vec4& other) {
		return !(this->x == other.x && this->y == other.y);
	}

	bool vec4::operator>(vec4& other) {

		return (this->sqrMagnitude() > other.sqrMagnitude());

	}

	bool vec4::operator<(vec4& other) {

		return (this->sqrMagnitude() < other.sqrMagnitude());

	}

	bool vec4::operator>=(vec4& other) {

		return (this->sqrMagnitude() >= other.sqrMagnitude());

	}

	bool vec4::operator<=(vec4& other) {

		return (this->sqrMagnitude() <= other.sqrMagnitude());

	}



	vec4 operator+(vec4 left, const vec4& right) {


		return left.add(right);

	}

	vec4 operator-(vec4 left, const vec4& right) {

		
		return left.sub(right);

	}

	vec4 operator*(vec4 left, const vec4& right) {

		return left.mult(right);;

	}

	vec4 operator/(vec4 left, const vec4& right) {

		return left.div(right);;

	}

	vec4 operator+(vec4 left, const float& right) {

		return left.add(right);

	}
	
	vec4 operator-(vec4 left, const float& right) {

		return left.sub(right);

	}
	
	vec4 operator*(vec4 left, const float& right) {

		return left.mult(right);

	}
	
	vec4 operator/(vec4 left, const float& right) {

		return left.div(right);

	}

	vec4 operator+(const float& left, vec4 right) {

		return right.add(left);

	}
	
	vec4 operator*(const float& left, vec4 right) {

		return right.mult(left);

	}
	


	std::ostream& operator<<(std::ostream& stream, vec4& vector) {

		stream << vector.toString();
		return stream;

	}



	float vec4::dot(const vec4& left, const vec4& right) {

		return left.x * right.x + left.y * right.y + left.z * left.z + left.w * left.w;

	}

	float vec4::distance(const vec4& left, const vec4& right) {

		return (left - right).magnitude();

	}

	float vec4::sqrDistance(const vec4& left, const vec4& right){

		return (left - right).sqrMagnitude();

	}
	
	vec4 vec4::lerp(const vec4& left, const vec4& right, const float& t){

		return ((right - left) * t) + left;


	}

	std::string vec4::toString() {

		return "(" + std::to_string(this->x) + " | " + std::to_string(this->y) + " | " + std::to_string(this->z) + " | " + std::to_string(this->w) + ")";

	}

}
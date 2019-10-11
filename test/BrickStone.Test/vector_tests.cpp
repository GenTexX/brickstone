#include "pch.h"
#include "math/ivec2.cpp"
using namespace bs;

#pragma region Fixture class

class ivec2Test : public ::testing::Test {
protected:
	void SetUp() override {
		a_ = ivec2(0, 1);
		b_ = ivec2(1, 0);
		c_ = ivec2(1, 1);
		d_ = ivec2(-1, -1);
		e_ = ivec2(-1, -1);
		f_ = ivec2(1, 1);
		g_ = ivec2(-1, 1);
		h_ = ivec2(1, -1);
		i_ = ivec2(1, -1);
		j_ = ivec2(-1, 1);
	}

	ivec2 a_;
	ivec2 b_;
	ivec2 c_;
	ivec2 d_;
	ivec2 e_;
	ivec2 f_;
	ivec2 g_;
	ivec2 h_;
	ivec2 i_;
	ivec2 j_;
};

#pragma endregion

TEST_F(ivec2Test, Add) {
	ivec2 ab = a_.add(b_);
	ivec2 cd = c_.add(d_);
	ivec2 ef = e_.add(f_);
	ivec2 gh = g_.add(h_);
	ivec2 ij = i_.add(j_);

	ASSERT_EQ(1, ab.x);
	ASSERT_EQ(1, ab.y);
	ASSERT_EQ(0, cd.x);
	ASSERT_EQ(0, cd.y);	
	ASSERT_EQ(0, ef.x);
	ASSERT_EQ(0, ef.y);	
	ASSERT_EQ(0, gh.x);
	ASSERT_EQ(0, gh.y);
	ASSERT_EQ(0, ij.x);
	ASSERT_EQ(0, ij.y);
}

TEST_F(ivec2Test, Sub) {
	ivec2 ab = a_.sub(b_);
	ivec2 cd = c_.sub(d_);
	ivec2 ef = e_.sub(f_);
	ivec2 gh = g_.sub(h_);
	ivec2 ij = i_.sub(j_);

	ASSERT_EQ(-1, ab.x);
	ASSERT_EQ(1, ab.y);
	ASSERT_EQ(2, cd.x);
	ASSERT_EQ(2, cd.y);
	ASSERT_EQ(-2, ef.x);
	ASSERT_EQ(-2, ef.y);
	ASSERT_EQ(-2, gh.x);
	ASSERT_EQ(2, gh.y);
	ASSERT_EQ(2, ij.x);
	ASSERT_EQ(-2, ij.y);
}

TEST(Math, ivec2_static_distance) {
	ivec2 a(3, 0);
	ivec2 b(0, 4);

}
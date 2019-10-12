#include "pch.h"
#include "math/ivec2.cpp"
using namespace bs;

#pragma region Fixture class

class ivec2_test : public ::testing::Test {
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

TEST_F(ivec2_test, Add) {
	ivec2 ab = a_.add(b_);
	ivec2 cd = c_.add(d_);
	ivec2 ef = e_.add(f_);
	ivec2 gh = g_.add(h_);
	ivec2 ij = i_.add(j_);

	EXPECT_EQ(1, ab.x);
	EXPECT_EQ(1, ab.y);
	EXPECT_EQ(0, cd.x);
	EXPECT_EQ(0, cd.y);	
	EXPECT_EQ(0, ef.x);
	EXPECT_EQ(0, ef.y);	
	EXPECT_EQ(0, gh.x);
	EXPECT_EQ(0, gh.y);
	EXPECT_EQ(0, ij.x);
	EXPECT_EQ(0, ij.y);
}

TEST_F(ivec2_test, Sub) {
	ivec2 ab = a_.sub(b_);
	ivec2 cd = c_.sub(d_);
	ivec2 ef = e_.sub(f_);
	ivec2 gh = g_.sub(h_);
	ivec2 ij = i_.sub(j_);

	EXPECT_EQ(-1, ab.x);
	EXPECT_EQ(1, ab.y);
	EXPECT_EQ(2, cd.x);
	EXPECT_EQ(2, cd.y);
	EXPECT_EQ(-2, ef.x);
	EXPECT_EQ(-2, ef.y);
	EXPECT_EQ(-2, gh.x);
	EXPECT_EQ(2, gh.y);
	EXPECT_EQ(2, ij.x);
	EXPECT_EQ(-2, ij.y);
}

TEST_F(ivec2_test, Magnitude) {
	EXPECT_FLOAT_EQ(1.0, a_.magnitude());
	EXPECT_FLOAT_EQ(1.0, b_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, c_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, d_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, e_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, f_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, g_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, h_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, i_.magnitude());
	EXPECT_FLOAT_EQ(1.4142135623f, j_.magnitude());
}

TEST_F(ivec2_test, SqrMagnitude) {
	EXPECT_EQ(1, a_.sqrMagnitude());
	EXPECT_EQ(1, b_.sqrMagnitude());
	EXPECT_EQ(2, c_.sqrMagnitude());
	EXPECT_EQ(2, d_.sqrMagnitude());
	EXPECT_EQ(2, e_.sqrMagnitude());
	EXPECT_EQ(2, f_.sqrMagnitude());
	EXPECT_EQ(2, g_.sqrMagnitude());
	EXPECT_EQ(2, h_.sqrMagnitude());
	EXPECT_EQ(2, i_.sqrMagnitude());
	EXPECT_EQ(2, j_.sqrMagnitude());
}

TEST_F(ivec2_test, Equals) {
	ASSERT_FALSE(a_.equals(b_));
	ASSERT_FALSE(c_.equals(d_));
	ASSERT_FALSE(e_.equals(f_));
	ASSERT_FALSE(g_.equals(h_));
	ASSERT_FALSE(i_.equals(j_));
}
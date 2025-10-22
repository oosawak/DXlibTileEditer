//**************************************************************
// Vector2ƒNƒ‰ƒX
// ì¬“úF 2023/10/01
// ì¬ÒF •St
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
class Vector2
{
public:
	float	X;
	float	Y;

	Vector2()
		: X(0.0f)
		, Y(0.0f)
	{}

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	// •¡‡‘ã“ü‚Ì‰ÁZ(a += b)
	Vector2& operator+=(const Vector2& right) {
		X += right.X;
		Y += right.Y;
		return *this;
	}

	// •¡‡‘ã“ü‚ÌŒ¸Z(a -= b)
	Vector2& operator-=(const Vector2& right) {
		X -= right.X;
		Y -= right.Y;
		return *this;
	}

	// •¡‡‘ã“ü‚ÌæZ(a *= scalar)
	Vector2& operator*=(float scalar) {
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	// ‰ÁZ(a + b)
	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.X + b.X, a.Y + b.Y);
	}

	// Œ¸Z(a - b)
	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.X - b.X, a.Y - b.Y);
	}

	// Œ¸Z(a * b)
	friend Vector2 operator*(const Vector2& a, const Vector2& b) {
		return Vector2(a.X * b.X, a.Y * b.Y);
	}

	// Œ¸Z(a * scalar)
	friend Vector2 operator*(const Vector2& a, float scalar) {
		return Vector2(a.X * scalar, a.Y * scalar);
	}

	// Œ¸Z(scalar * a)
	friend Vector2 operator*(float scalar, const Vector2& a) {
		return Vector2(a.X * scalar, a.Y * scalar);
	}

};


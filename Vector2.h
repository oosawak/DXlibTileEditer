//**************************************************************
// Vector2�N���X
// �쐬���F 2023/10/01
// �쐬�ҁF �S�t
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

	// ��������̉��Z(a += b)
	Vector2& operator+=(const Vector2& right) {
		X += right.X;
		Y += right.Y;
		return *this;
	}

	// ��������̌��Z(a -= b)
	Vector2& operator-=(const Vector2& right) {
		X -= right.X;
		Y -= right.Y;
		return *this;
	}

	// ��������̏�Z(a *= scalar)
	Vector2& operator*=(float scalar) {
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	// ���Z(a + b)
	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.X + b.X, a.Y + b.Y);
	}

	// ���Z(a - b)
	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.X - b.X, a.Y - b.Y);
	}

	// ���Z(a * b)
	friend Vector2 operator*(const Vector2& a, const Vector2& b) {
		return Vector2(a.X * b.X, a.Y * b.Y);
	}

	// ���Z(a * scalar)
	friend Vector2 operator*(const Vector2& a, float scalar) {
		return Vector2(a.X * scalar, a.Y * scalar);
	}

	// ���Z(scalar * a)
	friend Vector2 operator*(float scalar, const Vector2& a) {
		return Vector2(a.X * scalar, a.Y * scalar);
	}

};


/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_math.h"

Vec2::Vec2()
{
	X = 0;
	Y = 0;
}

Vec2::Vec2(float x, float y)
{
	X = x;
	Y = y;
}

Vec2& Vec2::operator*(float f)
{
	Vec2 Result;
	Result.X = X * f;
	Result.Y = Y * f;

	return Result;
}

Vec2& Vec2::operator*(Vec2 other)
{
	Vec2 Result;
	Result.X = X * other.X;
	Result.Y = Y * other.Y;

	return Result;
}

Vec2& Vec2::operator+(Vec2 other)
{
	Vec2 Result;
	Result.X = X + other.X;
	Result.Y = Y + other.Y;

	return Result;
}

Vec2& Vec2::operator-()
{
	Vec2 Result;
	Result.X = -X;
	Result.Y = -Y;

	return Result;
}

Vec2& Vec2::operator-(Vec2 other)
{
	Vec2 Result;
	Result.X = X - other.X;
	Result.Y = Y - other.Y;

	return Result;
}

Vec3::Vec3()
{
	X = 0;
	Y = 0;
	Z = 0;
}

Vec3::Vec3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vec3& Vec3::operator*(float f)
{
	Vec3 Result;
	Result.X = X * f;
	Result.Y = Y * f;
	Result.Z = Z * f;

	return Result;
}

Vec3& Vec3::operator*(Vec3 other)
{
	Vec3 Result;
	Result.X = X * other.X;
	Result.Y = Y * other.Y;
	Result.Z = Z * other.Z;

	return Result;
}

Vec3& Vec3::operator+(Vec3 other)
{
	Vec3 Result;
	Result.X = X + other.X;
	Result.Y = Y + other.Y;
	Result.Z = Z + other.Z;

	return Result;
}

Vec3& Vec3::operator-()
{
	Vec3 Result;
	Result.X = -X;
	Result.Y = -Y;
	Result.Z = -Z;

	return Result;
}

Vec3& Vec3::operator-(Vec3 other)
{
	Vec3 Result;
	Result.X = X - other.X;
	Result.Y = Y - other.Y;
	Result.Z = Z - other.Z;

	return Result;
}

Vec4::Vec4()
{
	X = 0;
	Y = 0;
	Z = 0;
	W = 0;
}

Vec4::Vec4(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

Vec4& Vec4::operator*(float f)
{
	Vec4 Result;
	Result.X = X * f;
	Result.Y = Y * f;
	Result.Z = Z * f;
	Result.W = W * f;

	return Result;
}

Vec4& Vec4::operator*(Vec4 other)
{
	Vec4 Result;
	Result.X = X * other.X;
	Result.Y = Y * other.Y;
	Result.Z = Z * other.Z;
	Result.W = W * other.W;

	return Result;
}

Vec4& Vec4::operator+(Vec4 other)
{
	Vec4 Result;
	Result.X = X + other.X;
	Result.Y = Y + other.Y;
	Result.Z = Z + other.Z;
	Result.W = W + other.W;

	return Result;
}

Vec4& Vec4::operator-()
{
	Vec4 Result;
	Result.X = -X;
	Result.Y = -Y;
	Result.Z = -Z;
	Result.W = -W;

	return Result;
}

Vec4& Vec4::operator-(Vec4 other)
{
	Vec4 Result;
	Result.X = X - other.X;
	Result.Y = Y - other.Y;
	Result.Z = Z - other.Z;
	Result.W = W - other.W;

	return Result;
}

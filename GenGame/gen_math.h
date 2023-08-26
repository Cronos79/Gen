/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

class Vec2
{
public:
	float X;
	float Y;
	Vec2();
	Vec2(float x, float y);
	Vec2& operator*(float f);
	Vec2& operator*(Vec2 other);
	Vec2& operator+(Vec2 other);
	Vec2& operator-();
	Vec2& operator-(Vec2 other);
};

class Vec3
{
public:
	float X;
	float Y;
	float Z;
	Vec3();
	Vec3(float x, float y, float z);
	Vec3& operator*(float f);
	Vec3& operator*(Vec3 other);
	Vec3& operator+(Vec3 other);
	Vec3& operator-();
	Vec3& operator-(Vec3 other);
};

class Vec4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	Vec4();
	Vec4(float x, float y, float z, float w);
	Vec4& operator*(float f);
	Vec4& operator*(Vec4 other);
	Vec4& operator+(Vec4 other);
	Vec4& operator-();
	Vec4& operator-(Vec4 other);
};


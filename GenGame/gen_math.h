/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

#include <Windowsnumerics.h>

#define Vec2 Windows::Foundation::Numerics::float2
#define Vec3 Windows::Foundation::Numerics::float3
#define Vec4 Windows::Foundation::Numerics::float4

inline float Square(float A)
{
	float Result = A * A;

	return A;
}

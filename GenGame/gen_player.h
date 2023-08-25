/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once
#include "gen_math.h"
#include <d2d1.h>
#include <stdint.h>

struct gen_player
{
	Vec3 Location;
	D2D1_COLOR_F Color;
	bool Fill;
	int32_t ZOrder;
};
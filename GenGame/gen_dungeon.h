/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once
#include <stdint.h>
#include <vector>

enum gen_sister_room
{
	ROOMUP,
	ROOMDOWN,
	ROOMLEFT,
	ROOMRIGHT
};

struct gen_rect
{
	int32_t top;
	int32_t bottom;
	int32_t left;
	int32_t right;
	gen_sister_room SisterRoom;
};

struct gen_tile
{	
	uint32_t Tile;
};

struct gen_room
{
	int32_t MaxRoomX = 29;
	int32_t MaxRoomY = 16;
	gen_rect Dim;
	std::vector<gen_tile> Tiles;
	gen_sister_room SisterRoom;
};
/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

enum TileType
{
	DIRT_FLOOR,
	STONE_WALL,
	DUNGEON_WOOD_DOOR
};

struct gen_tile
{
	TileType Type;
	int32_t DoorTo;
	bool IsDoor;
};
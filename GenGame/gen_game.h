/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once
#include <stdint.h>
#include <d2d1.h>
#include <vector>
#include "gen_math.h"
#include "gen_player.h"

#define bool32 int32_t

struct gen_drawable
{
	int32_t Row;
	int32_t Column;
	D2D1_COLOR_F Color;
	bool Fill;
	int32_t ZOrder;
};

// Tile stuff
struct gen_tile
{
	uint32_t Tile;
};

struct gen_tile_map
{
	gen_tile Tiles[];
};

// Input stuff
struct gen_input_button
{
	bool32 IsDown;
};

struct gen_input_analog
{
	float X;
	float Y;
};

struct gen_input
{	
	union
	{
		gen_input_button Buttons[14];
		struct
		{
			gen_input_button A;
			gen_input_button B;
			gen_input_button X;
			gen_input_button Y;

			gen_input_button DPadUp;
			gen_input_button DPadDown;
			gen_input_button DPadLeft;
			gen_input_button DPadRight;

			gen_input_button LeftShoulder;
			gen_input_button RightShoulder;

			gen_input_button LThumb;
			gen_input_button Rthumb;

			gen_input_button Back;
			gen_input_button Start;
		};		
	};
	union
	{
		gen_input_analog Analogs[4];
		struct
		{
			gen_input_analog LStick;
			gen_input_analog RStick;
			gen_input_analog LTrigger;
			gen_input_analog RTrigger;
		};
	};
	
};

struct game_state
{
	gen_player Player;
};

struct game_memory
{
	bool32 IsInitialized;
	std::vector<gen_drawable> Drawables;
	uint64_t PermanentStorageSize;
	void* PermanentStorage;
};

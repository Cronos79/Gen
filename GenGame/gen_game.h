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

#ifndef gendun
#define gendun
#include "gen_dungeon.cpp"
#endif

#if GEN_SLOW
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif

#define bool32 int32_t

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

struct gen_drawable
{
	int32_t Row;
	int32_t Column;
	D2D1_COLOR_F Color;
	bool Fill;
	int32_t ZOrder;
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
	std::vector<gen_room> Rooms;
	gen_room CurrentRoom;
	uint32_t CurrentRoomHeight = 0;
	uint32_t CurrentRoomWidth = 0;
};

struct game_memory
{
	bool32 IsInitialized;
	float DeltaTime;
	std::vector<gen_drawable> Drawables;
	uint64_t GameStorageSize;
	void* GameStorage;
};

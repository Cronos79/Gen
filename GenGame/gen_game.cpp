/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include "gen_game.h"
#include "gen_player.cpp"

/**********************************************************************************
* #TODO: Wish list
* Tiled world
* Hero
* AI NPC / Enemies 
* xinput
* xaudio2
* assimp
* asset mng
* sprites
* D2D
* D3D
* OpenGL
* Networking multiplayer
**********************************************************************************/

static void GenUpdate(game_memory* Memory, gen_input Input)
{
	Assert(sizeof(game_state) <= Memory->GameStorageSize);
	game_state* GameState = (game_state*)Memory->GameStorage;
	if (!Memory->IsInitialized)
	{
		gen_player Player = InitPlayer();
		GameState->Player = Player;
		GameState->Player.Location.X = 150;
		GameState->Player.Location.Y = 150;

		Memory->IsInitialized = true;
	}

	float PlayerSpeed = 8.0f;
	if (Input.A.IsDown)
	{
		PlayerSpeed = 30.0f;
	}
	else
	{
		PlayerSpeed = 8.0f;
	}
	if (Input.LStick.Y != 0.0f)
	{
		GameState->Player.Location.Y += -Input.LStick.Y * PlayerSpeed;
	}
	if (Input.LStick.X != 0.0f)
	{
		GameState->Player.Location.X += Input.LStick.X * PlayerSpeed;
	}

	uint32_t Tiles00[16][29] =
	{
		{1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 1},
		{1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, 1},
	};

	for (int Row = 0;
		Row < 16;
		++Row)
	{
		for (int Column = 0;
			Column < 29;
			++Column)
		{
			int32_t ttype = Tiles00[Row][Column];
			if (ttype == 0)
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::Gray);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}
			else
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::BurlyWood);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}
		}
	}
}

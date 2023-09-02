/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */

#include <stdio.h>
#include <vector>
#include "gen_game.h"
#include "gen_player.cpp"

/**********************************************************************************
* #TODO: Wish list
* Tiled world
* Collision
* Working doors
* AI NPC / Enemies 
* xaudio2
* assimp
* asset mng
* sprites
* D3D
* OpenGL
* Networking multiplayer
**********************************************************************************/



static void GenUpdate(game_memory* Memory, gen_input Input)
{
	Assert(sizeof(game_state) <= Memory->GameStorageSize);
	game_state* GameState = (game_state*)Memory->GameStorage;	
	
	TileType tiletype;
	if (!Memory->IsInitialized)
	{
		gen_player Player = InitPlayer();
		GameState->Player = Player;
		GameState->Player.Location.x = 3;
		GameState->Player.Location.y = 3;
		GameState->Player.Velocity.x = 0;
		GameState->Player.Velocity.y = 0;
		GameState->Player.Velocity.z = 0;

		GameState->Rooms = GenDungeon(200, 200);
		GameState->CurrentRoom = GameState->Rooms.at(0);
		GameState->CurrentRoomHeight = GameState->CurrentRoom.Dim.bottom - GameState->CurrentRoom.Dim.top;
		GameState->CurrentRoomWidth = GameState->CurrentRoom.Dim.right - GameState->CurrentRoom.Dim.left;

		Memory->IsInitialized = true;			
	}

	MovePlayer(GameState, Input, Memory->DeltaTime);	

	Memory->Drawables.clear();
	int32_t pos = 0;
	for (int Row = 0;
		Row < GameState->CurrentRoomHeight;
		++Row)
	{
		for (int Column = 0;
			Column < GameState->CurrentRoomWidth;
			++Column)
		{
			tiletype = GameState->CurrentRoom.Tiles.at(pos++).Type;

			switch (tiletype)
			{
			case DIRT_FLOOR: 
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::Gray);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}break;
			case STONE_WALL:
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::BurlyWood);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}break;
			case DUNGEON_WOOD_DOOR:
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::Brown);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}break;
			default:
			{
				gen_drawable d = {};
				d.Column = Column;
				d.Row = Row;
				d.Color = D2D1::ColorF(D2D1::ColorF::Fuchsia);
				d.Fill = true;
				Memory->Drawables.push_back(d);
			}break;
			}
		}
	}
}

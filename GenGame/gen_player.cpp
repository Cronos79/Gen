/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_player.h"
#include "gen_game.h"

static gen_player InitPlayer()
{
	gen_player Player;
	Player.Location = Vec3();
	Player.Color = D2D1::ColorF(D2D1::ColorF::Gold);
	Player.Fill = true;
	Player.ZOrder = 10;

	return Player;
}

static void MovePlayer(game_state* GameState, gen_input Input, float DeltaTime)
{
	float PlayerSpeed = 2.25f * DeltaTime;
	if (Input.A.IsDown)
	{
		PlayerSpeed = 6.5f * DeltaTime;
	}
	else
	{
		PlayerSpeed = 2.25f * DeltaTime;
	}

	if (Input.LStick.Y != 0.0f)
	{
		GameState->Player.Location.Y += -Input.LStick.Y * PlayerSpeed;
		if (Input.LStick.Y > 0.0f)
		{
			GameState->Player.Facing = PlayerFacing::UP;
		}
		else
		{
			GameState->Player.Facing = PlayerFacing::DOWN;
		}
	}
	if (Input.LStick.X != 0.0f)
	{
		GameState->Player.Location.X += Input.LStick.X * PlayerSpeed;
		if (Input.LStick.X < 0.0f)
		{
			GameState->Player.Facing = PlayerFacing::LEFT;
		}
		else
		{
			GameState->Player.Facing = PlayerFacing::RIGHT;
		}
	}	
}
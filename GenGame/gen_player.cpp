/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_player.h"
#include "gen_game.h"
#include "gen_math.h"

static gen_player InitPlayer()
{
	gen_player Player;
	Player.Location = Vec3(3,3,0);
	Player.Color = D2D1::ColorF(D2D1::ColorF::Gold);
	Player.Fill = true;
	Player.ZOrder = 10;

	return Player;
}

static void MovePlayer(game_state* GameState, gen_input Input, float DeltaTime)
{
	Vec3 Acceleration = {};
	if (Input.LStick.Y != 0.0f)
	{
		Acceleration.y += -Input.LStick.Y;
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
		Acceleration.x += Input.LStick.X;
		if (Input.LStick.X < 0.0f)
		{
			GameState->Player.Facing = PlayerFacing::LEFT;
		}
		else
		{
			GameState->Player.Facing = PlayerFacing::RIGHT;
		}
	}

	if ((Acceleration.x != 0.0f) && (Acceleration.y != 0.0f))
	{
		Acceleration *= 0.707106781187f;
	}

	float PlayerSpeed = 5.0f; // #NOTE: m/s^2
	if (Input.A.IsDown)
	{
		PlayerSpeed = 25.0f;
	}

	Acceleration *= PlayerSpeed;	

	Acceleration += -1.5f * GameState->Player.Velocity;

	Vec3 NewPlayerP = GameState->Player.Location;

	NewPlayerP = (0.5f * Acceleration * Square(DeltaTime) +
		GameState->Player.Velocity * DeltaTime +
		NewPlayerP);
	GameState->Player.Velocity = Acceleration * DeltaTime + GameState->Player.Velocity;

	GameState->Player.Location = NewPlayerP;

	// Bounce off wall
	/*Vec3 Wall = {0,1,0}; // -2 bounces -1 slides on wall
	GameState->Player.Velocity = GameState->Player.Velocity - 2 * DotProduct(GameState->Player.Velocity, Wall) * Wall;*/
}
/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_game.h"
#include <Windows.h>
#include <stdio.h>

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

static void GenUpdate(gen_input Input, float DeltaTime)
{
	if (Input.LStick.Y != 0.0f)
	{
		char buffer[256];
		_snprintf_s(buffer, sizeof(buffer),
			"%.02fX %.02fY\n", Input.LStick.X, Input.LStick.Y);
		OutputDebugStringA(buffer);
	}
	if (Input.A.IsDown)
	{
		OutputDebugStringA("buffer");
	}
}

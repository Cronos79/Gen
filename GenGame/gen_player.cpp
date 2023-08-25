/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_player.h"

static gen_player InitPlayer()
{
	gen_player Player;
	Player.Location = Vec3();
	Player.Color = D2D1::ColorF(D2D1::ColorF::Gold);
	Player.Fill = true;
	Player.ZOrder = 10;

	return Player;
}
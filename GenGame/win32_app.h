/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

#include "win32_window.h"
#include "gen_game.h"

class win32_app
{
public:
	win32_app(const std::string& commandLine = "");
	// master frame / message loop
	int Begin();
	~win32_app();
private:
	void HandleInput(float dt);
	void Update(float dt);	
private:
	std::string commandLine;
	bool showDemoWindow = false;
	win32_window wnd;
	//ChiliTimer timer;
	float speed_factor = 1.0f;
	gen_input Input;
};


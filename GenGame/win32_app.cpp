/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "win32_app.h"
#include "gen_game.cpp"

win32_app::win32_app(const std::string& commandLine /*= ""*/)
	: commandLine(commandLine),
	wnd(1280, 720, "Gen Engine")
{}

win32_app::~win32_app()
{}

int win32_app::Begin()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = win32_window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		const auto dt = 1.0f;//timer.Mark() * speed_factor;
		HandleInput(dt);
		Update(dt);
	}
}

void win32_app::HandleInput(float dt)
{
	Input.LStick.X = 1.0f;
	Input.A.IsDown = true;
}

void win32_app::Update(float dt)
{
	UpdateAndRender(Input, dt);
}

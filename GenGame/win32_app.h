/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

#include "win32_window.h"
#include "gen_game.h"
#include "win32_timer.h"

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
	void Render(float dt);
	void EnforceFrameRate(LARGE_INTEGER& LastCounter, bool SleepIsGranular, float TargetSecondsPerFrame, uint64_t& LastCycleCount);
	inline LARGE_INTEGER Win32GetWallClock(void)
	{
		LARGE_INTEGER Result;
		QueryPerformanceCounter(&Result);
		return(Result);
	}
	inline float Win32GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
	{
		float Result = ((float)(End.QuadPart - Start.QuadPart) /
			(float)GlobalPerfCountFrequency);
		return(Result);
	}
private:
	int64_t GlobalPerfCountFrequency;
	std::string commandLine;
	bool showDemoWindow = false;
	win32_window wnd;
	win32_timer timer;
	gen_input Input;
};


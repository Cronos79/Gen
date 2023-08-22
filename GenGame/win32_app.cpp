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
	int MonitorRefreshHz = 60;
	HDC RefreshDC = GetDC(wnd.hWnd);
	int Win32RefreshRate = GetDeviceCaps(RefreshDC, VREFRESH);
	ReleaseDC(wnd.hWnd, RefreshDC);
	if (Win32RefreshRate > 1)
	{
		MonitorRefreshHz = Win32RefreshRate;
	}
	float GameUpdateHz = (MonitorRefreshHz);
	float TargetSecondsPerFrame = 1.0f / (float)GameUpdateHz;
	bool SleepIsGranular = true;
	LARGE_INTEGER LastCounter;
	QueryPerformanceCounter(&LastCounter);
	uint64_t LastCycleCount = __rdtsc();


	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = win32_window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		const auto dt = timer.Mark();
		HandleInput(dt);
		Update(dt);
		Render(dt);
		EnforceFrameRate(LastCounter, SleepIsGranular, TargetSecondsPerFrame, LastCycleCount);
	}
}

void win32_app::HandleInput(float dt)
{	
	if (wnd.kbd.KeyIsPressed('W'))
	{
		Input.LStick.Y = 1.0f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		Input.LStick.Y = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		Input.LStick.X = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		Input.LStick.X = 1.0f;
	}
}

void win32_app::Update(float dt)
{
	GenUpdate(Input, dt);
}

void win32_app::Render(float dt)
{
	// Render sprites from game
}

void win32_app::EnforceFrameRate(LARGE_INTEGER &LastCounter, bool SleepIsGranular, float TargetSecondsPerFrame, uint64_t& LastCycleCount)
{
	LARGE_INTEGER WorkCounter = Win32GetWallClock();
	float WorkSecondsElapsed = Win32GetSecondsElapsed(LastCounter, WorkCounter);

	// TODO: NOT TESTED YET!  PROBABLY BUGGY!!!!!
	float SecondsElapsedForFrame = WorkSecondsElapsed;
	if (SecondsElapsedForFrame < TargetSecondsPerFrame)
	{
		if (SleepIsGranular)
		{
			DWORD SleepMS = (DWORD)(1000.0f * (TargetSecondsPerFrame -
				SecondsElapsedForFrame));
			if (SleepMS > 0)
			{
				Sleep(SleepMS);
			}
		}

		float TestSecondsElapsedForFrame = Win32GetSecondsElapsed(LastCounter,
			Win32GetWallClock());
		if (TestSecondsElapsedForFrame < TargetSecondsPerFrame)
		{
			// TODO: LOG MISSED SLEEP HERE
		}

		/*while (SecondsElapsedForFrame < TargetSecondsPerFrame)
		{
			SecondsElapsedForFrame = Win32GetSecondsElapsed(LastCounter,
				Win32GetWallClock());
		}*/
	}
	else
	{
		// TODO: MISSED FRAME RATE!
		// TODO: Logging
	}

	LARGE_INTEGER EndCounter = Win32GetWallClock();
	float MSPerFrame = 1000.0f * Win32GetSecondsElapsed(LastCounter, EndCounter);
	LastCounter = EndCounter;

	uint64_t EndCycleCount = __rdtsc();
	uint64_t CyclesElapsed = EndCycleCount - LastCycleCount;
	LastCycleCount = EndCycleCount;
#if 0
	double MCPF = ((double)CyclesElapsed / (1000.0f * 1000.0f));

	char FPSBuffer[256];
	_snprintf_s(FPSBuffer, sizeof(FPSBuffer),
		"%.02fmc/f\n", MCPF);
	OutputDebugStringA(FPSBuffer);
#endif	
}

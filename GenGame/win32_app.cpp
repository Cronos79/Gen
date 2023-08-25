/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "win32_app.h"
#include "gen_game.cpp"
#include <Xinput.h>

win32_app::win32_app(const std::string& commandLine /*= ""*/)
	: commandLine(commandLine),
	wnd(1920, 1080, "Gen Engine")
{
	Input = {};
	GlobalPerfCountFrequency = 0;
}

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

	//game_state State;
	
	GameMemory = {};
	GameMemory.GameStorageSize = Gigabytes(4);
#if GEN_INTERNAL
	LPVOID BaseAddress = (LPVOID)Terabytes(2);
#else
	LPVOID BaseAddress = 0;
#endif
	void* GameMemoryBlock = VirtualAlloc(BaseAddress, (size_t)GameMemory.GameStorageSize,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	GameMemory.GameStorage = GameMemoryBlock;
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
		EnforceFrameRate(LastCounter, SleepIsGranular, TargetSecondsPerFrame, LastCycleCount, dt);
	}
}

void win32_app::HandleInput(float dt)
{	
	// #TODO: Finish all buttons
	float LXNorm = 0.0f;
	float LYNorm = 0.0f;
	bool AIsDown = false;
	bool BIsDown = false;
	bool XIsDown = false;
	bool YIsDown = false;
	Input = {};
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_GAMEPAD* Pad = nullptr;
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			Pad = &state.Gamepad;

			float LX = Pad->sThumbLX;
			float LY = Pad->sThumbLY;

			LXNorm = Win32ProcessXInputStickValue(LX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			LYNorm = Win32ProcessXInputStickValue(LY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

			AIsDown = ((Pad->wButtons & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A);
			BIsDown = ((Pad->wButtons & XINPUT_GAMEPAD_B) == XINPUT_GAMEPAD_B);
			XIsDown = ((Pad->wButtons & XINPUT_GAMEPAD_X) == XINPUT_GAMEPAD_X);
			YIsDown = ((Pad->wButtons & XINPUT_GAMEPAD_Y) == XINPUT_GAMEPAD_Y);
		}
		else
		{
			// Controller is not connected
		}
	}		

	// Move code
	if (LYNorm != 0.0f)
	{
		Input.LStick.Y = LYNorm;
	}
	if (LXNorm != 0.0f)
	{
		Input.LStick.X = LXNorm;
	}
	
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

	// buttons	
	if (wnd.kbd.KeyIsPressed('1') || AIsDown)
	{
		Input.A.IsDown = true;
	}
	if (wnd.kbd.KeyIsPressed('2') || BIsDown)
	{
		Input.B.IsDown = true;
	}
	if (wnd.kbd.KeyIsPressed('3') || XIsDown)
	{
		Input.X.IsDown = true;
	}
	if (wnd.kbd.KeyIsPressed('4') || YIsDown)
	{
		Input.Y.IsDown = true;
	}
}

void win32_app::Update(float dt)
{	
	GameMemory.DeltaTime = dt;
	GenUpdate(&GameMemory, Input);
}

void win32_app::Render(float dt)
{
	int size = 64;
	wnd.D2D().RT()->BeginDraw();	

	for (gen_drawable& drawable : GameMemory.Drawables)
	{
		auto c = D2D1::ColorF(drawable.Color.r, drawable.Color.g, drawable.Color.b, drawable.Color.a);
		wnd.D2D().DrawRect(D2D1::RectF(size * drawable.Column, size * drawable.Row, (size * drawable.Column) + size, (size * drawable.Row) + size), c);
		
	}
	wnd.D2D().RT()->EndDraw();
}

void win32_app::EnforceFrameRate(LARGE_INTEGER &LastCounter, bool SleepIsGranular, float TargetSecondsPerFrame, uint64_t& LastCycleCount, float dt)
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
		"%.02fmc/f %.04fDeltaTime\n", MCPF, dt);
	OutputDebugStringA(FPSBuffer);
#endif	
}

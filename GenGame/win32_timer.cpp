/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "win32_timer.h"

using namespace std::chrono;

win32_timer::win32_timer() noexcept
{
	last = steady_clock::now();
}

float win32_timer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float win32_timer::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - last).count();
}

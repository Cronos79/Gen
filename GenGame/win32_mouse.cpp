/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "win32_mouse.h"
#include "win32_window.h"

std::pair<int, int> win32_mouse::GetPos() const noexcept
{
	return { x,y };
}

std::optional<win32_mouse::RawDelta> win32_mouse::ReadRawDelta() noexcept
{
	if (rawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta d = rawDeltaBuffer.front();
	rawDeltaBuffer.pop();
	return d;
}

int win32_mouse::GetPosX() const noexcept
{
	return x;
}

int win32_mouse::GetPosY() const noexcept
{
	return y;
}

bool win32_mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool win32_mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool win32_mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

std::optional<win32_mouse::Event> win32_mouse::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		win32_mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return {};
}

void win32_mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void win32_mouse::EnableRaw() noexcept
{
	rawEnabled = true;
}

void win32_mouse::DisableRaw() noexcept
{
	rawEnabled = false;
}

bool win32_mouse::RawEnabled() const noexcept
{
	return rawEnabled;
}

void win32_mouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void win32_mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void win32_mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void win32_mouse::OnRawDelta(int dx, int dy) noexcept
{
	rawDeltaBuffer.push({ dx,dy });
	TrimBuffer();
}

void win32_mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void win32_mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void win32_mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::RPress, *this));
	TrimBuffer();
}

void win32_mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void win32_mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void win32_mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(win32_mouse::Event(win32_mouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void win32_mouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

void win32_mouse::TrimRawInputBuffer() noexcept
{
	while (rawDeltaBuffer.size() > bufferSize)
	{
		rawDeltaBuffer.pop();
	}
}

void win32_mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	// generate events for every 120 
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}

/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "win32_keyboard.h"

bool win32_keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

std::optional<win32_keyboard::Event> win32_keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		win32_keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	return {};
}

bool win32_keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

void win32_keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

std::optional<char> win32_keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	return {};
}

bool win32_keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void win32_keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void win32_keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void win32_keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void win32_keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool win32_keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void win32_keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(win32_keyboard::Event(win32_keyboard::Event::Type::Press, keycode));
	TrimBuffer(keybuffer);
}

void win32_keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(win32_keyboard::Event(win32_keyboard::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void win32_keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void win32_keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void win32_keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}
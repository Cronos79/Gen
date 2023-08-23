/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once
#include "win32_win.h"
#include "win32_exception.h"
#include <optional>
#include <vector>
#include "win32_keyboard.h"
#include "win32_mouse.h"
#include "win32_d2d.h"
#include <memory>

class win32_window
{
public:
	class Exception : public win32_exception
	{
		using win32_exception::win32_exception;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Gen Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	win32_window(int width, int height, const char* name);
	~win32_window();
	win32_window(const win32_window&) = delete;
	win32_window& operator=(const win32_window&) = delete;
	void SetTitle(const std::string& title);
	void EnableCursor() noexcept;
	void DisableCursor() noexcept;
	bool CursorEnabled() const noexcept;
	static std::optional<int> ProcessMessages() noexcept;
private:
	void ConfineCursor() noexcept;
	void FreeCursor() noexcept;
	void ShowCursor() noexcept;
	void HideCursor() noexcept;
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	win32_keyboard kbd;
	win32_mouse mouse;
	HWND hWnd;
private:
	bool cursorEnabled = true;
	int width;
	int height;	
	std::vector<BYTE> rawBuffer;
	std::string commandLine;
	std::unique_ptr<win32_d2d> pGfx;
};


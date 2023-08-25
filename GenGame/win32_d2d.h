/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once
#include "win32_win.h"
#include <d2d1.h>
#include <wrl/module.h>

class win32_d2d
{
public:
	win32_d2d(HWND hWnd, int width, int height);
	win32_d2d(const win32_d2d&) = delete;
	win32_d2d& operator=(const win32_d2d&) = delete;
	~win32_d2d();
public:
	ID2D1HwndRenderTarget* RT();
	void DrawRect(D2D1_RECT_F Rect, D2D1::ColorF Color, bool Fill = true);
	void DrawPlayer(D2D1_RECT_F Rect, D2D1::ColorF Color, bool Fill = true);
private:
	Microsoft::WRL::ComPtr<ID2D1Factory> pD2DFactory;
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> pRT;
};


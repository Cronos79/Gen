#include "win32_d2d.h"

win32_d2d::win32_d2d(HWND hWnd, int width, int height)
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		pD2DFactory.GetAddressOf()
	);

	// Obtain the size of the drawing area.
	RECT rc;
	GetClientRect(hWnd, &rc);

	// Create a Direct2D render target  
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);	
}

win32_d2d::~win32_d2d()
{

}

ID2D1HwndRenderTarget* win32_d2d::RT()
{
	return pRT.Get();
}

void win32_d2d::DrawRect(D2D1_RECT_F Rect, D2D1::ColorF Color, bool Fill)
{
	if (!pRT) { return; }
	ID2D1SolidColorBrush* pBrush = NULL;
	pRT->CreateSolidColorBrush(D2D1::ColorF(Color), &pBrush);
	
	if (pBrush)
	{
		if (Fill)
		{
			pRT->FillRectangle(Rect, pBrush);
		}
		else
		{
			pRT->DrawRectangle(Rect, pBrush);
		}		
		pBrush->Release();
	}		
}

void win32_d2d::DrawRect(Vec2 Rect, D2D1::ColorF Color, bool Fill /*= true*/)
{
	DrawRect(D2D1::RectF(PixelsPerMeter * Rect.x, PixelsPerMeter * Rect.y, (PixelsPerMeter * Rect.x) + PixelsPerMeter,
		(PixelsPerMeter * Rect.y) + PixelsPerMeter), Color);
}

void win32_d2d::DrawPlayer(D2D1_RECT_F Rect, D2D1::ColorF Color, bool Fill /*= true*/)
{
	if (!pRT) { return; }
	ID2D1SolidColorBrush* pBrush = NULL;
	pRT->CreateSolidColorBrush(D2D1::ColorF(Color), &pBrush);

	if (pBrush)
	{
		if (Fill)
		{
			pRT->FillRectangle(Rect, pBrush);
		}
		else
		{
			pRT->DrawRectangle(Rect, pBrush);
		}
		pBrush->Release();
	}
}

void win32_d2d::DrawPlayer(Vec2 Rect, D2D1::ColorF Color, bool Fill /*= true*/)
{
	DrawPlayer(D2D1::RectF(Rect.x * PixelsPerMeter, Rect.y * PixelsPerMeter, (Rect.x * PixelsPerMeter) + 40.0f, (Rect.y * PixelsPerMeter) + 60.0f), Color, Fill);
}

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

	ID2D1SolidColorBrush* pBlackBrush = NULL;
	if (SUCCEEDED(hr))
	{

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&pBlackBrush
		);
	}

	ID2D1SolidColorBrush* pRedBrush = NULL;
	if (SUCCEEDED(hr))
	{

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&pRedBrush
		);
	}

	pRT->BeginDraw();

	pRT->DrawRectangle(
		D2D1::RectF(
			/*rc.left + 100.0f,
			rc.top + 100.0f,
			rc.right - 100.0f,
			rc.bottom - 100.0f),*/
			0,
			0,
			128,
			128),
		pRedBrush);

	hr = pRT->EndDraw();
	
	pBlackBrush->Release();
	pRedBrush->Release();
}

win32_d2d::~win32_d2d()
{

}

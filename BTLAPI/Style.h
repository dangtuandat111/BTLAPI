#pragma once
#include <wtypes.h>
class CStyle
{
	HPEN _hPen;
	int _iStyle;
	int _iWidth;
	COLORREF _color;
public:
	CStyle()
	{
		_iStyle = PS_SOLID;
		_iWidth = 1;
		_color = RGB(0, 0, 0);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	CStyle(int iStyle, int iWidth, COLORREF color, COLORREF bgcolor)
	{
		_iStyle = iStyle;
		_iWidth = iWidth;
		_color = color;
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	CStyle(const CStyle& st)
	{
		if (&st != NULL)
		{
			_iStyle = st._iStyle;
			_iWidth = st._iWidth;
			_color = st._color;
			_hPen = CreatePen(_iStyle, _iWidth, _color);
		}
	}
	~CStyle() {}
	void SetStyle(int iStyle)
	{
		_iStyle = iStyle;
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	void SetWidth(int iWidth) {
		_iWidth = iWidth;
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	void SetColor(COLORREF color) {
		_color = color;
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}

	void SetHDCPen(HDC hdc)
	{
		SelectObject(hdc, _hPen);
	}

	int GetStyle() { return _iStyle; }
	int GetWidth() { return _iWidth; }
	COLORREF GetColor() { return _color; }
};


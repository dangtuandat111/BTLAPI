// BTLAPI.cpp : Defines the entry point for the application.
//
#pragma once
#include "framework.h"
#include "BTLAPI.h"
#include <vector>

#include <xstring>
#include <string>
#include "SaveFile.h"
#include <commdlg.h>
#include <CommCtrl.h>
#include "minwinbase.h"
#include "ReadFile.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwndShape[20], hwndMauNen[20], hwndMauVien[20], hwndGroupBox[20], hwndSize[20], hwndStyleBrush[5];
HWND hwndChonVien, hwndChonNen, hwndStyle,hwndCurrentSize, hwndStatusBar;
static COLORREF color[10] = { RGB(255, 255, 255) ,RGB(195, 195, 195),RGB(185, 122, 87) ,RGB(255, 174, 201) ,RGB(255, 201, 14) ,
									RGB(239, 228, 176) ,  RGB(181, 230, 29) , RGB(153, 217, 234) , RGB(112, 146, 190) , RGB(200, 191, 231) };
static HWND hwndDrawArea;
int numShape = 15; 
int numMauVien = 15;
int numMauNen = 15; 
int num = 15;
static HWND hwndMain;
static int currentShape = 0 ;
static COLORREF currentMauNen = RGB(255, 255, 255);
static COLORREF currentMauVien = RGB(0, 0, 0);
static COLORREF currentSize = 1;
static int currentStyle = 0;
static HDC hdc;

int exist = 0;

HDC temp_hdc;
HWND temp_hWnd;
HPEN temp_hPen;
HBRUSH temp_hBrush;
#define ID_DRAW_AREA 200

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Funtion
void DrawLine(HDC hdc, int left, int top, int right, int bottom);
void DrawIsosceleTriangle(HDC hdc, int left, int top, int right, int bottom);
void DrawTriangle(HDC hdc, int left, int top, int right, int bottom);
void DrawQuadrilateral(HDC hdc, int left, int top, int right, int bottom);
void DrawPentagon(HDC hdc, int left, int top, int right, int bottom);
void DrawHexagon(HDC hdc, int left, int top, int right, int bottom);
void DrawForwardArrow(HDC hdc, int left, int top, int right, int bottom);
void DrawBackArrow(HDC hdc, int left, int top, int right, int bottom);
void DrawDownArrow(HDC hdc, int left, int top, int right, int bottom);
void DrawUpArrow(HDC hdc, int left, int top, int right, int bottom);
void DrawFourPointStar(HDC hdc, int left, int top, int right, int bottom);
void DrawFivePointStar(HDC hdc, int left, int top, int right, int bottom);
void DrawSixPointStar(HDC hdc, int left, int top, int right, int bottom);
void DrawLightning(HDC hdc, int left, int top, int right, int bottom);
void DrawRoundRect(HDC hdc, int left, int top, int right, int bottom);
void DrawInline(HBRUSH hbrush,HWND hWnd, COLORREF color[]);
void setToolBox(HDC hdc, HWND hWnd, HPEN hPen, HBRUSH hBrush);
void SaveImage();
void ExportImage();
void OpenImage();
void OpenBitmapByFileName(wstring openFilename);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BTLAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BTLAPI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BTLAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BTLAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd1 = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
	   0, 0, 50, 50, nullptr, nullptr, hInstance, nullptr);
   hwndMain = hWnd1;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int N = 10;
	static int i;
	static TCHAR labelGroup[][20] = { TEXT("NỀN"),TEXT("VIỀN"),TEXT("MORE"),TEXT("SIZE"),TEXT("STYLE") };
	static TCHAR labelSize[][20] = { TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5") };
	
	//static COLORREF color[5] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255),RGB(255,255,0),RGB(0,255,255) };
	//static COLORREF color[10] = { RGB(255, 154, 162) , RGB(255, 183, 178),RGB(255, 218, 193) ,RGB(226, 240, 203) ,RGB(181, 234, 215) ,
	//								RGB(199, 206, 234) , RGB(236, 228, 197) , RGB(225, 196, 245) , RGB(255, 249, 244) , RGB(180, 181, 181) };
	
	static HBRUSH hbrushMaunut;
	static HBRUSH hBrushHinh = CreateSolidBrush(RGB(255, 255, 255));
	static HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	static int Hinh = 0, xLeft, yTop, xRight, yBottom;

	CHOOSECOLOR  cc; 
	COLORREF  acrCustClr[16];
	DWORD  rgbCurrent = RGB(0, 0, 0); 
	HBRUSH  hbrush; 
	int newColor = 0;

	int count = 0;
	int row = 0;
	int column = 0;

    switch (message)
    {
	case WM_SIZE: //khi kích thước cửa sổ chính của chương trình thay đổi mới chạy vào phần này, khi mới chạy chương trình cũng nhảy vào đây
	{
		if (exist == 0) {
			setToolBox(temp_hdc, hWnd, temp_hPen, temp_hBrush);
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			MoveWindow(hWnd, 200, 150, 990, 600, TRUE);
			exist = 1;
		}
		
		
		break;
	}
	case WM_CREATE: {
		hwndGroupBox[0] = CreateWindow(TEXT("BUTTON"), TEXT("SHAPE"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 20, 160, 130, hWnd, (HMENU)(16), NULL, NULL);
		
		//0-14
		while (true) {
			hwndShape[count] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20 + row * 30, 50 + column * 30, 20, 20, hWnd, (HMENU)(count), NULL, NULL);
			count++;
			if (count == 15)  break;
			row++;
			if (row >= 5) {
				row = 0;
				column++;
			}
		}
		//16-25
		hwndGroupBox[1] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 962, 160, hWnd, (HMENU)(17), NULL, NULL);
		for (i = 2;i < 4;i++) {
			hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230, 20, 225, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		}
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 + 5 , 20, 80, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 - 153, 20, 85, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		//56
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 200 - 170, 20, 150, 130, hWnd, (HMENU)(56), NULL, NULL);
		//57-60
		for (i = 57;i <= 60;i++) {
			hwndStyleBrush[i - 57] = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 815, 40 + (i-57) * 30 , 30, 15, hWnd, (HMENU)(i), NULL, NULL);
		}
		//58
		//hwndCurrentColor = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 965, 20, 100, 130, hWnd, (HMENU)(58), NULL, NULL);
		//59
		//hwndCurrentSize = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 1070, 20, 50, 130, hWnd, (HMENU)(59), NULL, NULL);
		hwndDrawArea = CreateWindow(TEXT("static"), TEXT("DRAW"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 962, 340, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
		//26-36
		//37-46
		row = 0;
		column = 0;
		for (i = 0;i < 10;i++) {
			
			hwndMauNen[i] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 185 + row * 40 + 8, 50 + 40 * (column + column * 0.125), 35, 35, hWnd, (HMENU)(i + 26), NULL, NULL);
			hwndMauVien[i] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 415 + row * 40 + 8, 50 + 40 * (column + column * 0.125), 35, 35, hWnd, (HMENU)(i + 37), NULL, NULL);
			if (i < 5) {
				//48-53
				hwndSize[i + 1] = CreateWindow(TEXT("BUTTON"), labelSize[i], WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 735, 42 + i * 20, 50, 18, hWnd, (HMENU)(i + 48), NULL, NULL);
			}

			row++;
			if (row >= 5) {
				row = 0;column++;
			}
		}
		//54-55
		i = 0;
		hwndChonNen = CreateWindow(TEXT("BUTTON"), TEXT("NỀN"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 650, 55, 60, 30, hWnd, (HMENU)(i + 54), NULL, NULL);
		hwndChonVien = CreateWindow(TEXT("BUTTON"), TEXT("VIỀN"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 650, 90, 60, 30, hWnd, (HMENU)(i + 55), NULL, NULL);
		
		
		hwndStatusBar = CreateWindowEx(0, STATUSCLASSNAME, (PCTSTR)NULL, SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
				0,0,0,0, hWnd, NULL, hInst, NULL);

		RECT rectStatusBar;

		int Parts[] = { 80, 250, 420, 970};
		SendMessage(hwndStatusBar, SB_SETPARTS, 4, (LPARAM)Parts);

		// tạo text cho status bar
		SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)L"Ready");

		WCHAR buffer[15];
		swprintf_s(buffer, 15, L"%d x %d",660, 100);
		SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);

		SendMessage(hwndStyleBrush[0], BM_SETCHECK, 1, 0);
		break;
	}
	case WM_MOUSEMOVE:
		if (LOWORD(lParam) >= 6 && HIWORD(lParam) >= 166 && LOWORD(lParam) <= 965 && HIWORD(lParam) <= 504) { OnMouseMove(hWnd, LOWORD(lParam) - 6, HIWORD(lParam) - 166, TRUE); }
		else OnMouseMove(hWnd, 0, 0, TRUE);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case 0: 
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
				currentShape = wmId;
				Hinh = currentShape;
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
				currentMauNen = color[wmId - 26];
				hBrushHinh = CreateSolidBrush(currentMauNen);
				/*
				PAINTSTRUCT ps;
				hdc = BeginPaint(hwndCurrentColor, &ps);
				SelectObject(hdc, hBrushHinh);
				Rectangle(hdc, 2, 10, 97, 127);
				EndPaint(hwndCurrentColor, &ps);
				*/
				
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			case 37:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
				currentMauVien = color[wmId - 37];
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				
				InvalidateRect(hWnd, NULL, FALSE);
				break;

			case 48: {
				currentSize = wmId - 47;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}

				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			case 49: {
				currentSize = wmId - 47;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			case 50: {
				currentSize = wmId - 46;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			case 51: {
				currentSize = wmId - 47;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .Set size = 1",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			case 52: {
				currentSize = wmId - 47;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			
				
			case 54:
			{
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&cc))
				{
					acrCustClr[newColor] = cc.rgbResult;
					newColor++;
					currentMauNen = cc.rgbResult;
					hBrushHinh = CreateSolidBrush(currentMauNen);
				}
				
				ReleaseDC(hWnd, hdc);
				break;
			}
			case 55:
			{
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&cc))
				{
					currentMauVien = cc.rgbResult;
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				
				ReleaseDC(hWnd, hdc);
				break;
			}

			case 57: {
				currentStyle = wmId - 57;
				hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				InvalidateRect(hWnd, NULL, FALSE);
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				break;
			}
			case 58: {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				currentStyle = wmId - 57;
				hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				InvalidateRect(hWnd, NULL, FALSE);
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				break;
			}	
			case 59: {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				currentStyle = wmId - 57;
				hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				InvalidateRect(hWnd, NULL, FALSE);
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				break;
			}	
			case 60: {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				currentStyle = wmId - 57;
				hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				InvalidateRect(hWnd, NULL, FALSE);
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				break;
			}
				  
			case ID_FILE_SAVE:
				ExportImage();
				break;
			case IDM_FILE_NEW: 
				hwndDrawArea = CreateWindow(TEXT("static"), TEXT("Draw"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 1125, 340, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
				break;
			case ID_FILE_OPEN:
			{
				OpenImage();
				break;
			}
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
            case IDM_EXIT:
				if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
					DestroyWindow(hWnd);
				}
				break;
			case ID_FILE_EXIT:
				if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không?"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
					DestroyWindow(hWnd);
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
		xLeft = LOWORD(lParam);
		yTop = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
	{
		xRight = LOWORD(lParam);
		yBottom = HIWORD(lParam);
		if (yTop <= 160 | xLeft <= 5 | yBottom <= 160 | xRight <= 5 | yTop > 505 | yBottom > 505) break;
		//xLeft += 160;
		yTop -= 165;
		//xRight += 160;
		yBottom -= 165;

		hdc = GetDC(hwndDrawArea);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrushHinh);
		if (Hinh == 0) {
			DrawLine(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 1) {
			DrawIsosceleTriangle(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 2) {
			DrawTriangle(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 3) {
			DrawQuadrilateral(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 4) {
			DrawPentagon(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 5) {
			DrawHexagon(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 6) {
			DrawForwardArrow(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 7) {
			DrawBackArrow(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 8) {
			DrawDownArrow(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 9) {
			DrawUpArrow(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 10) {
			DrawFourPointStar(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 11) {
			DrawFivePointStar(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 12) {
			DrawSixPointStar(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 13) {
			Rectangle(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 14) {
			DrawRoundRect(hdc, xLeft, yTop, xRight, yBottom);
		}
		ReleaseDC(hWnd, hdc);
		break;
	}
	
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
			//DrawInline(hbrushMaunut,hWnd,color);
            // TODO: Add any drawing code that uses hdc here...
			break;
        }
	case WM_CLOSE: 
		if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
			DestroyWindow(hWnd);
		}
		else {
			break;
		}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
void DrawLine(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[2];
	p[0].x = left;
	p[0].y = top;
	p[1].x = right;
	p[1].y = bottom;
	Polyline(hdc, p, 2);
}
void DrawIsosceleTriangle(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left + (right - left) / 2;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}
void DrawTriangle(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}
void DrawQuadrilateral(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[5];
	p[4].x = p[0].x = left + (right - left) / 2;
	p[4].y = p[0].y = top;

	p[1].y = p[3].y = top + (bottom - top) / 2;
	p[1].x = right;

	p[2].x = left + (right - left) / 2;
	p[2].y = bottom;

	p[3].x = left;
	Polygon(hdc, p, 5);
}
void DrawPentagon(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[6];
	p[5].x = p[0].x = left + (right - left) / 2;
	p[5].y = p[0].y = top;

	p[1].x = left;
	p[1].y = p[4].y = top + 2 * (bottom - top) / 5;

	p[2].x = left + (right - left) / 5;
	p[2].y = p[3].y = bottom;

	p[3].x = left + 4 * (right - left) / 5;

	p[4].x = right;
	Polygon(hdc, p, 6);
}
void DrawHexagon(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[7];
	p[6].x = p[0].x = p[3].x = left + (right - left) / 2;
	p[6].y = p[0].y = top;

	p[2].x = p[1].x = left;
	p[1].y = p[5].y = top + (bottom - top) / 4;
	p[4].x = p[5].x = right;

	p[2].y = p[4].y = top + 3 * (bottom - top) / 4;

	p[3].y = bottom;
	Polygon(hdc, p, 7);
}
void DrawForwardArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = left;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = right;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}
void DrawBackArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = right;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = left;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}
void DrawDownArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = top;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = bottom;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}
void DrawUpArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = bottom;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = top;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}
void DrawFourPointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[9];
	p[4].x = p[8].x = p[0].x = left + (right - left) / 2;
	p[8].y = p[0].y = top;

	p[1].x = p[3].x = left + 2 * (right - left) / 5;
	p[1].y = p[7].y = top + 2 * (bottom - top) / 5;

	p[2].x = left;
	p[2].y = p[6].y = top + (bottom - top) / 2;

	p[3].y = p[5].y = top + 3 * (bottom - top) / 5;
	p[4].y = bottom;

	p[5].x = p[7].x = left + 3 * (right - left) / 5;
	p[6].x = right;
	Polygon(hdc, p, 9);
}
void DrawFivePointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[11];
	p[10].x = p[0].x = left + (right - left) / 2;
	p[10].y = p[0].y = top;
	p[1].x = left + 10 * (right - left) / 16;
	p[1].y = top + 3 * (bottom - top) / 8;

	p[2].x = right;
	p[2].y = top + 3 * (bottom - top) / 8; //=p1

	p[3].x = left + 5 * (right - left) / 7;
	p[3].y = top + 5 * (bottom - top) / 8;

	p[4].x = left + 5 * (right - left) / 6;
	p[4].y = bottom;

	p[5].x = left + (right - left) / 2;
	p[5].y = top + 3 * (bottom - top) / 4;

	p[6].x = left + (right - left) / 6;
	p[6].y = bottom;

	p[7].x = left + 2 * (right - left) / 7;
	p[7].y = top + 5 * (bottom - top) / 8;

	p[8].x = left;
	p[8].y = top + 3 * (bottom - top) / 8;

	p[9].x = left + 6 * (right - left) / 16;
	p[9].y = top + 3 * (bottom - top) / 8;
	Polygon(hdc, p, 11);
}
void DrawSixPointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[13];
	p[6].x = p[12].x = p[0].x = left + (right - left) / 2;
	p[12].y = p[0].y = top;

	p[5].x = p[1].x = left + (right - left) / 3;
	p[10].y = p[11].y = p[2].y = p[1].y = top + (bottom - top) / 4;

	p[4].x = p[2].x = left;
	p[3].x = left + (right - left) / 6;
	p[9].y = p[3].y = top + (bottom - top) / 2;

	p[8].y = p[7].y = p[5].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[6].y = bottom;

	p[11].x = p[7].x = left + 2 * (right - left) / 3;
	p[10].x = p[8].x = right;
	p[9].x = left + 5 * (right - left) / 6;

	Polygon(hdc, p, 13);
}
void DrawLightning(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}

	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}

	POINT p[12];
	p[11].x = p[0].x = left + 8 * (right - left) / 20;
	p[11].y = p[0].y = top;

	p[1].x = left;
	p[1].y = top + 4 * (bottom - top) / 20;

	p[2].x = left + 7 * (right - left) / 20;
	p[2].y = top + 8 * (bottom - top) / 20;

	p[3].x = left + 5 * (right - left) / 20;
	p[3].y = top + 9 * (bottom - top) / 20;

	p[4].x = left + 11 * (right - left) / 20;
	p[4].y = top + 13 * (bottom - top) / 20;

	p[5].x = left + 10 * (right - left) / 20;
	p[5].y = top + 14 * (bottom - top) / 20;

	p[6].x = right;
	p[6].y = bottom;

	p[7].x = left + 14 * (right - left) / 20;
	p[7].y = top + 12 * (bottom - top) / 20;

	p[8].x = left + 15 * (right - left) / 20;
	p[8].y = top + 11 * (bottom - top) / 20;

	p[9].x = left + 21 * (right - left) / 40;
	p[9].y = top + 7 * (bottom - top) / 20;

	p[10].x = left + 12 * (right - left) / 20;
	p[10].y = top + 6 * (bottom - top) / 20;
	Polygon(hdc, p, 12);
}
void DrawRoundRect(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}

	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}

	int width = (right - left) * 20 / 100;
	int height = (bottom - top) * 20 / 100;
	RoundRect(hdc, left, top, right, bottom, width, height);
}
void DrawInline(HBRUSH hbrushMaunut,HWND hWnd, COLORREF color[]) {
	PAINTSTRUCT ps;
	
	hdc = BeginPaint(hwndShape[0], &ps);
	DrawLine(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[1], &ps);
	DrawIsosceleTriangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[2], &ps);
	DrawTriangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[3], &ps);
	DrawQuadrilateral(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[4], &ps);
	DrawPentagon(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[5], &ps);
	DrawHexagon(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[6], &ps);
	DrawForwardArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[7], &ps);
	DrawBackArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[8], &ps);
	DrawDownArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[9], &ps);
	DrawUpArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[10], &ps);
	DrawFourPointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[11], &ps);
	DrawFivePointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[12], &ps);
	DrawSixPointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[13], &ps);
	Rectangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[14], &ps);
	DrawRoundRect(hdc, 5, 5, 15, 15);
	
	for (int i = 0;i < 10;i++) {
		hbrushMaunut = CreateSolidBrush(color[i]);

		hdc = BeginPaint(hwndMauNen[i], &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 33, 33);
		EndPaint(hwndMauNen[i], &ps);

		hdc = BeginPaint(hwndMauVien[i], &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 33, 33);
		DeleteObject(hbrushMaunut);
		EndPaint(hwndMauVien[i], &ps);
	}

	EndPaint(hwndShape[0], &ps);
	EndPaint(hWnd, &ps);
	InvalidateRect(hWnd, NULL, FALSE);
	ReleaseDC(hWnd, hdc);
}
void SaveImage() {
	
	int result = MessageBox(hwndDrawArea, L"Do u wanna save file??", L"Save Image", MB_YESNO | MB_ICONQUESTION);
	if (result == 6) {
		ExportImage();
	}
}
void ExportImage() {
	OPENFILENAME ofn;
	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = hwndMain;
	
	ofn.lpstrFilter = L"JPEG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bin";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"bmp";

	if (GetSaveFileName(&ofn))
	{
		wstring ws(szFileName);
		/////////////////Handle Save Bmp
		//string fileName(ws.begin(), ws.end());
		//HDC -> HBitMap

		HDC hDC = GetDC(hwndDrawArea);
		HDC hTargetDC = CreateCompatibleDC(hDC);
		RECT rect = { 0 };
		GetWindowRect(hwndDrawArea, &rect);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right - rect.left,
			rect.bottom - rect.top);
		SelectObject(hTargetDC, hBitmap);
		//PrintWindow(hwndDrawArea, hTargetDC, PW_CLIENTONLY);
		BitBlt(hTargetDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
		PBITMAPINFO pbmi = CreateBitmapInfoStruct(hwndDrawArea, hBitmap);
		CreateBMPFile(hwndDrawArea, ws.c_str(), pbmi, hBitmap, hDC);
		DeleteObject(hBitmap);
		ReleaseDC(hwndDrawArea, hDC);
		DeleteDC(hTargetDC);
	}
}
void setToolBox(HDC hdc, HWND hWnd, HPEN hPen, HBRUSH hBrush) {
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwndShape[0], &ps);
	DrawLine(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[1], &ps);
	DrawIsosceleTriangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[2], &ps);
	DrawTriangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[3], &ps);
	DrawQuadrilateral(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[4], &ps);
	DrawPentagon(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[5], &ps);
	DrawHexagon(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[6], &ps);
	DrawForwardArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[7], &ps);
	DrawBackArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[8], &ps);
	DrawDownArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[9], &ps);
	DrawUpArrow(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[10], &ps);
	DrawFourPointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[11], &ps);
	DrawFivePointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[12], &ps);
	DrawSixPointStar(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[13], &ps);
	DrawLightning(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[14], &ps);
	Rectangle(hdc, 5, 5, 15, 15);

	hdc = BeginPaint(hwndShape[14], &ps);
	DrawRoundRect(hdc, 5, 5, 15, 15);
	/*
	hBrush = CreateSolidBrush(currentMauNen);
	hdc = BeginPaint(hwndCurrentColor, &ps);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 2, 10, 97, 127);
	EndPaint(hwndCurrentColor, &ps);
	*/

	for (int i = 0;i < 10;i++) {
		hBrush = CreateSolidBrush(color[i]);

		hdc = BeginPaint(hwndMauNen[i], &ps);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 2, 2, 33, 33);
		EndPaint(hwndMauNen[i], &ps);

		hdc = BeginPaint(hwndMauVien[i], &ps);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 2, 2, 33, 33);
		DeleteObject(hBrush);
		EndPaint(hwndMauVien[i], &ps);
	}
	hdc = GetDC(hWnd);

	hPen = CreatePen(PS_SOLID, currentSize, RGB(0,0,0));
	SelectObject(hdc, hPen);

	POINT point[2];
	point[0].x = 850;
	point[0].y = 50;
	point[1].x = 950;
	point[1].y = 50;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DOT, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	point[0].x = 850;
	point[0].y = 80;
	point[1].x = 950;
	point[1].y = 80;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DASHDOT, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	point[0].x = 850;
	point[0].y = 110;
	point[1].x = 950;
	point[1].y = 110;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DASH, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	point[0].x = 850;
	point[0].y = 140;
	point[1].x = 950;
	point[1].y = 140;
	Polyline(hdc, point, 2);

	/*
	hPen = CreatePen(currentStyle, currentSize, currentMauVien);
	SelectObject(hdc, hPen);
	point[0].x = 1093;
	point[0].y = 35;
	point[1].x = 1093;
	point[1].y = 140;
	Polyline(hdc, point, 2);
	*/

	EndPaint(hwndShape[0], &ps);
	EndPaint(hWnd, &ps);
	InvalidateRect(hWnd, NULL, FALSE);
	ReleaseDC(hWnd, hdc);
}
void OpenImage() {
	OPENFILENAME ofn;
	WCHAR szFilePath[MAX_PATH] = L"";
	WCHAR szFileTitle[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndMain;
	ofn.lpstrFilter = L"Bitmap Files (*.bmp)\0*.bin\0PNG (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg";
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"bmp";
	static wstring openFilename;
	static bool isOpenFile = false;
	static int orderOpen = 0;
	if (GetOpenFileName(&ofn))
	{
		wstring ws(szFilePath);
		//string fileName(ws.begin(), ws.end());
		openFilename = ws;
		isOpenFile = true;
		OpenBitmapByFileName(openFilename);
	}
}
void OpenBitmapByFileName(wstring openFilename) {
	HBITMAP       hBitmap, hOldBitmap;
	HPALETTE      hPalette, hOldPalette;
	HDC           hMemDC;
	BITMAP        bm;
	HDC hDC = GetDC(hwndDrawArea);

	if (LoadBitmapFromBMPFile(openFilename.c_str(), &hBitmap, &hPalette))
	{
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		hMemDC = CreateCompatibleDC(hDC);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		hOldPalette = SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC); //nhan dang mau

							 // copy hMemDC to hdc
		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight,
			hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitmap);
		SelectPalette(hDC, hOldPalette, FALSE);
		DeleteObject(hPalette);
	}
}
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	WCHAR buffer[15];
	swprintf_s(buffer, 15, L"%d x %d", x, y);
	SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);
}


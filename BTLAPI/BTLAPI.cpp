// BTLAPI.cpp : Defines the entry point for the application.
//
#pragma once
#include "framework.h"
#include "BTLAPI.h"
#include <vector>

#include <windowsx.h>
#include <iostream>
#include <vector>

#include <xstring>
#include <string>
#include "SaveFile.h"
#include <commdlg.h>
#include <CommCtrl.h>
#include "minwinbase.h"
#include "ReadFile.h"
#include "Paint.h"

#include "stdafx.h"

//Bat dau sua lan 1
#include "olectl.h"
#include <wingdi.h>
#define ID_TEXT 420
#define ID_TEXTBOX 69420
//Ket thuc sua lan 1

#pragma comment(lib, "Gdi32.lib")

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
static int xLeft=0, yTop=0, xRight=0, yBottom=0;
int exist = 0;
PaintLibrary::CShape* pointer;
PaintLibrary::CShape* pointer2;
vector<PaintLibrary::CShape*> shapes;
vector<PaintLibrary::CShape*> temp;

int temp_firstX;
int temp_firstY;
int temp_lastX;
int temp_lastY;

bool isbegin = false;
bool isDraw = false;
bool isClick = false;
bool isErase = false;
bool isTesting = false;
bool pointerSelected = FALSE;

int kBrush = -1;

int start = 0;

PaintLibrary::CShape* tempShape;
PaintLibrary::CShape* currShape;

//Bat dau sua lan 2
HPEN hPenCurCol, hPenCurBorCol;
HBRUSH hBrushCurCol, hBrushCurBorCol;
HWND hwndCurCol, hwndTextBox[10], hwndTools, btnText;
HFONT g_hfFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
COLORREF g_rgbText = RGB(0, 0, 0);
COLORREF g_rgbBackground = RGB(255, 255, 255);
COLORREF g_rgbCustom[16] = { 0 };
COLORREF Colortem[10];
BOOLEAN isTyping = false;
static int iTextBox = 0;
int countTextBox;
int fontSize;
TCHAR buff[1024];
//Ket thuc sua lan 2

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
void DrawDT(HDC hdc, int left, int top, int right, int bottom);
void DrawTGC(HDC hdc, int left, int top, int right, int bottom);
void DrawTGV(HDC hdc, int left, int top, int right, int bottom);
void DrawHT(HDC hdc, int left, int top, int right, int bottom);
void DrawNG(HDC hdc, int left, int top, int right, int bottom);
void DrawLG(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Right(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Left(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Down(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_UP(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_4(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_5(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_6(HDC hdc, int left, int top, int right, int bottom);
void DrawHCN(HDC hdc, int left, int top, int right, int bottom);
void DrawInline(HBRUSH hbrush,HWND hWnd, COLORREF color[]);
void setToolBox(HBRUSH hbrush,HWND hWnd, COLORREF color[]);
void SaveImage();
void ExportImage();
void OpenImage();
void OpenBitmapByFileName(wstring openFilename);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove2(HWND hwnd, int x, int y, UINT keyFlags);


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
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
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
	static TCHAR labelGroup[][20] = { TEXT("BACKGROUND"),TEXT("BORDER"),TEXT("MORE"),TEXT("SIZE"),TEXT("STYLE") };
	static TCHAR labelSize[][20] = { TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5") };
	
	//static COLORREF color[5] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255),RGB(255,255,0),RGB(0,255,255) };
	//static COLORREF color[10] = { RGB(255, 154, 162) , RGB(255, 183, 178),RGB(255, 218, 193) ,RGB(226, 240, 203) ,RGB(181, 234, 215) ,
	//								RGB(199, 206, 234) , RGB(236, 228, 197) , RGB(225, 196, 245) , RGB(255, 249, 244) , RGB(180, 181, 181) };
	
	static HBRUSH hbrushMaunut;
	static HBRUSH hBrushHinh = CreateSolidBrush(RGB(255, 255, 255));
	static HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	static int Hinh = 0;

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
	//Bat dau sua lan 3
	case WM_CTLCOLOREDIT:
	{ 
		//for (int item = 0; item < iTextBox; item++) {
		//	if ((HWND)lParam == GetDlgItem(hWnd, ID_TEXTBOX + iTextBox - item -1))
		//	{
		//		/*SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));*/
		//		SetTextColor((HDC)wParam, Colortem[item]);
		//		return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
		//	}
		//}

		if ((HWND)lParam == GetDlgItem(hWnd, ID_TEXTBOX + iTextBox -1 ))
		{
			/*SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));*/
			for (int item = 0; item < iTextBox; item++) {
				GetDlgItem(hWnd, ID_TEXTBOX + iTextBox - item - 1);
				SetTextColor((HDC)wParam, Colortem[item]);
				//return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
			}

		}

		break;
	}
	//Ket thuc sua lan 3
	case WM_SIZE: //khi kích thước cửa sổ chính của chương trình thay đổi mới chạy vào phần này, khi mới chạy chương trình cũng nhảy vào đây
	{
		DrawInline(hbrushMaunut, hWnd, color);
		//khong su dung set tool box vi se ve lai ca size nua 
		if (exist == 0) {
			
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			MoveWindow(hWnd, 90, 150, 1350, 600, TRUE);
			exist = 1;
		}
		
		
		break;
	}
	case WM_CREATE: {
		hwndGroupBox[0] = CreateWindow(TEXT("BUTTON"), TEXT(" "), WS_CHILD | WS_VISIBLE | BS_GROUPBOX |BS_ICON, 10, 20, 160, 130, hWnd, (HMENU)(16), NULL, NULL);
		HICON hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONSHAPE));
		SendMessage(hwndGroupBox[0], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon2));
		
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
		//Bat dau sua lan 4 (chinh kich co window)
		hwndGroupBox[1] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 1320, 160, hWnd, (HMENU)(17), NULL, NULL);
		//Ket thuc sua lan 4
		for (i = 2;i < 4;i++) {
			hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), TEXT(" "), WS_CHILD | WS_VISIBLE | BS_GROUPBOX |BS_ICON, 180 + (i - 2) * 230, 20, 225, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		}
		hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONBACKGROUND));
		SendMessage(hwndGroupBox[2], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon2));
		hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONBACKGROUND));
		SendMessage(hwndGroupBox[3], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon2));
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), TEXT(" "), WS_CHILD | WS_VISIBLE | BS_GROUPBOX |BS_ICON, 180 + (i - 2) * 230 + 5 , 20, 80, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONCOLORPICKER));
		SendMessage(hwndGroupBox[4], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon2));
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 - 153, 20, 85, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		//56
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 200 - 170, 20, 150, 130, hWnd, (HMENU)(56), NULL, NULL);
		//57-60
		for (i = 57;i <= 60;i++) {
			hwndStyleBrush[i - 57] = CreateWindow(TEXT("button"), NULL, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 820, 42 + (i-57) * 30 , 15, 15, hWnd, (HMENU)(i), NULL, NULL);
		}
		//58
		//hwndCurrentColor = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 965, 20, 100, 130, hWnd, (HMENU)(58), NULL, NULL);
		//59
		//hwndCurrentSize = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 1070, 20, 50, 130, hWnd, (HMENU)(59), NULL, NULL);
		//Bat dau sua lan 5 (Tao groupbox cho mau dang chon,groupbox text,nut Text)
		hwndCurCol = CreateWindow(TEXT("button"), TEXT("CURRENT COLOR"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX , 965, 20, 150, 130, hWnd, (HMENU)NULL, NULL, NULL);
		//hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONCURRENT));

		SendMessage(hwndCurCol, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon2));
		hwndTools = CreateWindow(TEXT("button"), TEXT("TOOLS"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 1120, 20, 200, 130, hWnd, (HMENU)NULL, NULL, NULL);
		btnText = CreateWindow(TEXT("BUTTON"), TEXT("T"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1130, 40, 35, 35, hWnd, (HMENU)ID_TEXT, NULL, NULL);
		//Ket thuc sua lan 5
		
		//hWnd, 200, 150, 1350, 600, TRUE
		hwndDrawArea = CreateWindow(TEXT("static"), TEXT("DRAW"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 1319, 348, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
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
		hwndChonNen = CreateWindow(TEXT("BUTTON"), TEXT("NỀN"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_ICON , 650, 55, 60, 30, hWnd, (HMENU)(i + 54), NULL, NULL);
		hwndChonVien = CreateWindow(TEXT("BUTTON"), TEXT("VIỀN"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_ICON, 650, 90, 60, 30, hWnd, (HMENU)(i + 55), NULL, NULL);
		HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwndChonNen, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon));
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
		SendMessage(hwndChonVien, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(hIcon));
		
		hwndStatusBar = CreateWindowEx(0, STATUSCLASSNAME, (PCTSTR)NULL, SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
				0,0,0,0, hWnd, NULL, hInst, NULL);

		RECT rectStatusBar;

		int Parts[] = { 80, 250, 650, 1500};
		SendMessage(hwndStatusBar, SB_SETPARTS, 4, (LPARAM)Parts);

		// tạo text cho status bar
		SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)L"Ready");

		WCHAR buffer[15];
		swprintf_s(buffer, 15, L"%d x %d",670, 130);
		SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);

		SendMessage(hwndStyleBrush[0], BM_SETCHECK, 1, 0);


		break;
	}
	case WM_MOUSEMOVE:
		if (isTesting) {
			temp_lastX = LOWORD(lParam);
			temp_lastY = HIWORD(lParam);
			if (pointerSelected == FALSE)
			{
				currShape->SetData(temp_firstX, temp_firstY, temp_lastX, temp_lastY, currentMauVien, currentStyle, currentSize);
				currShape->SetBrush(RGB(255,255,255));
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
			{
				pointer->SetData(temp_firstX, temp_firstY, temp_lastX, temp_lastY, RGB(0, 0, 0), PS_DASH, 1);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		
		else {
			if (LOWORD(lParam) >= 6 && HIWORD(lParam) >= 166 && LOWORD(lParam) <= 1325 && HIWORD(lParam) <= 511)
			{
				if (isDraw == true) {
					OnMouseMove(hWnd, LOWORD(lParam) - 6, HIWORD(lParam) - 166, TRUE);
				}
				if (isErase == true) {
					OnMouseMove2(hWnd, LOWORD(lParam) - 6, HIWORD(lParam) - 166, TRUE);
				}
				OnMouseMove(hWnd, LOWORD(lParam) - 6, HIWORD(lParam) - 166, TRUE);
			}
			else {
				OnMouseMove(hWnd, 0, 0, TRUE);
			}
		}
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
					else hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
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
					
					else hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
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
					else hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .Set size = 1",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
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
					
					else hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					
					else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 .",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					else hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			
				
			case 54:
			{
				//memset(&cc, 0, sizeof(CHOOSECOLOR));
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&cc))
				{
					acrCustClr[newColor] = cc.rgbResult;
					newColor++;
					currentMauNen = cc.rgbResult;
					hBrushHinh = CreateSolidBrush(currentMauNen);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				ReleaseDC(hWnd, hdc);
				break;
			}
			case 55:
			{
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = acrCustClr;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&cc))
				{
					currentMauVien = cc.rgbResult;
					if (currentStyle == 0) {
						hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
					}
					else if(currentStyle == 1){
						hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
					}
					else if(currentStyle == 2) {
						hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
					}
					else if(currentStyle == 3) {
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
						}
					}
				InvalidateRect(hWnd, NULL, FALSE);
				ReleaseDC(hWnd, hdc);
				break;
			}

			case 57: {
				currentStyle = wmId - 57;
				hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				
				SendMessage(hwndStyleBrush[currentStyle], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				InvalidateRect(hWnd, NULL, FALSE);
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
				
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				InvalidateRect(hWnd, NULL, FALSE);
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
				
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				InvalidateRect(hWnd, NULL, FALSE);
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
				
				SendMessage(hwndStyleBrush[currentStyle ], BM_SETCHECK, 1, 0);
				for (int vitri = 0; vitri < 4; vitri++) {
					if (vitri == (currentStyle )) continue;
					SendMessage(hwndStyleBrush[vitri], BM_SETCHECK, 0, 0);
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			/*case ID_OPTION_TESTING: 
				isbegin = true;
				break;*/
				//Bat dau sua lan 6
			case ID_OPTION_TEXT:
				//if (!isTyping) {
				//	isTyping = true;
				//}
				//else {
				//	isTyping = false;
				//	//SetWindowLongA(GetDlgItem(hwndTextBox, ID_OPTION_TEXT), GWL_STYLE, 0);
				//	SetWindowLongPtr(hwndTextBox, GWL_STYLE, ES_READONLY);
				//	//SetWindowPos(hwndTextBox, NULL, 0,0, 0, 0, SWP_FRAMECHANGED);
				//	
				//}
				//SendDlgItemMessage(hwndTextBox, EM_SETREADONLY, TRUE, 0, 0);
				break;

			case ID_TEXT:
				if (!isTyping) {
					isTyping = true;
					countTextBox = 1;
					isDraw = false;
					isErase = false;
					isTesting = false;
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"Text");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);

				}
				else {
					isTyping = false;
					for (int j = 0; j < iTextBox; j++) {
						SetWindowLongPtr(hwndTextBox[j], GWL_STYLE, ES_READONLY);
					}
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);
				}
				break;
			case ID_OPTION_FONT: {
				CHOOSEFONT cf = { sizeof(CHOOSEFONT) };
				LOGFONT lf;

				GetObject(g_hfFont, sizeof(LOGFONT), &lf);

				cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
				cf.hwndOwner = hWnd;
				cf.lpLogFont = &lf;
				cf.rgbColors = g_rgbText;
				cf.iPointSize = fontSize;

				if (ChooseFont(&cf))
				{
					HFONT hf = CreateFontIndirect(&lf);
					if (hf)
					{
						g_hfFont = hf;
						SendDlgItemMessage(hWnd, ID_TEXTBOX + iTextBox -1 , WM_SETFONT, (WPARAM)g_hfFont, TRUE);
					}
					else
					{
						MessageBoxA(hWnd, "Lỗi Font", "Thông báo", MB_OK | MB_ICONEXCLAMATION);
					}

					g_rgbText = cf.rgbColors;

				}
			}
							   break;

			case ID_OPTION_FONTCOLOR: {
				PAINTSTRUCT ps;
				HDC hdc;
				HPEN hPenTextBox;
				hdc = BeginPaint(hwndTextBox[1], &ps);
				/*hPenTextBox = CreatePen(PS_SOLID, 1, currentMauVien);
				SelectObject(hdc, hPenTextBox);*/
				SetTextColor(hdc, RGB(250, 0, 0));
				//OPENFILENAME ofn;
				//WCHAR szFilePath[MAX_PATH] = L"";
				//WCHAR szFileTitle[MAX_PATH] = L"";

				//ZeroMemory(&ofn, sizeof(ofn));

				//ofn.lStructSize = sizeof(ofn);
				//ofn.hwndOwner = hwndMain;
				//ofn.lpstrFilter = L"JPEG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bin";
				//ofn.lpstrFile = szFilePath;
				//ofn.lpstrFileTitle = szFileTitle;
				//ofn.nMaxFile = MAX_PATH;
				//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				//if (GetOpenFileName(&ofn))
				//{
				//	HBITMAP hm = GetHBITMAPFromImageFile(szFilePath);
				//	//hm = LoadImage(NULL, szFilePath, IMAGE_BITMAP, 150, 150, LR_LOADFROMFILE);
				//	MessageBox(hWnd, szFilePath, TEXT(""), MB_OK);
				//	
				//}
				//else {
				//	MessageBox(hWnd, TEXT("Error"), TEXT(""), MB_OK);
				//}

			}
			break;
			//Ket thuc sua lan 6
			case ID_FILE_SAVE:
				ExportImage();
				break;
			case IDM_FILE_NEW: 
				//hWnd, 200, 150, 1350, 600, TRUE
				hwndDrawArea = CreateWindow(TEXT("static"), TEXT("DRAW"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 1319, 348, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
				break;
			case ID_KIND_HORIZONTAL:
				kBrush = 0;
				break;
			case ID_KIND_BDIAGONAL:
				kBrush = 1;
				break;
			case ID_KIND_VERTICAL:
				kBrush = 2;
				break;
			case ID_KIND_CROSS:
				kBrush = 3;
				break;
			case ID_KIND_FDIAGONAL:
				kBrush = 4;
				break;
			case ID_KIND_DIAGCROSS:
				kBrush = 5;
				break;
			case ID_KIND_SOLID: 
				kBrush = 6;
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
			case ID_OPTION_DRAW:
				if (isDraw == true) {
					isDraw = false;
					isClick = false;
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);
					break;
				}
				else
				{
					isDraw = true;
					isClick = false;
					isErase = false;
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"Draw");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);
				}
				break;
			case ID_OPTION_ERASE:
				if (isErase == true) {
					isErase = false;
					isClick = false;
					isTyping = false;
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);
				}
				else {
					isClick = false;
					temp_hBrush = CreateSolidBrush(RGB(255, 255, 255));
					temp_hPen = CreatePen(PS_SOLID, currentSize, RGB(255, 255, 255));
					isErase = true;
					isDraw = false;
					WCHAR buffer[15];
					swprintf_s(buffer, 15, L"Erase");
					SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);
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
	case WM_LBUTTONDOWN: {
		xLeft = LOWORD(lParam);
		yTop = HIWORD(lParam);
		isClick = true;
		//ReleaseDC(hWnd, hdc);
		pointer = NULL;
		pointer2 = NULL;
		//InvalidateRect(hWnd, NULL, TRUE);
		temp_firstX = LOWORD(lParam);
		temp_firstY = HIWORD(lParam);
		//Bat dau sua lan 7
		//LoadLibrary(TEXT("Msftedit.dll"));
		if (isTyping) { //&& countTextBox==1
			//WS_SIZEBOX
			if (yTop <= 165 | xLeft <= 5  | yTop > 511 |  xLeft >= 1320 ) break;
			Colortem[iTextBox] = currentMauVien;
			hwndTextBox[iTextBox] = CreateWindow(TEXT("edit"), TEXT(""),
				ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_SIZEBOX,
				xLeft, yTop, 100, 50, hWnd, (HMENU)(ID_TEXTBOX + iTextBox), NULL, NULL);
			HDC temp_hdcText = GetDC(hwndTextBox[iTextBox]);

			SetBkColor(temp_hdcText, TRANSPARENT);
			ReleaseDC(hWnd,temp_hdcText);
			iTextBox++;
			//countTextBox=2;
			xLeft = 0; 
			yTop = 0;
			break;
		}
		/*if(countTextBox==2){
			MessageBox(hWnd, TEXT("Chỉ được tồn tại 1 ô text"), TEXT("Thông báo"), MB_OK);
		}*/
		//ReleaseDC(hWnd, hdc);
		//Ket thuc sua lan 7
		if (!isTesting && isbegin == true) {
			isTesting = TRUE;
			if (pointerSelected == FALSE)
			{
				currShape = new PaintLibrary::CLine();
				/*switch (Hinh)
				{
				case 0:
					currShape = new PaintLibrary::CLine();
					break;
				case 1:
					currShape = new PaintLibrary::CRectangle();
					break;
				case 2:
					currShape = new PaintLibrary::CSquare();
					break;
				case 3:
					currShape = new PaintLibrary::CEllipse();
					break;
				case 4:
					currShape = new PaintLibrary::CCircle();
					break;
				case 5:
					currShape = new PaintLibrary::CArrow();
					break;
				case 6:
					currShape = new PaintLibrary::CStar();
					break;
				}*/
				currShape->SetType(Hinh);
				currShape->SetData(temp_firstX, temp_firstY, temp_firstX, temp_firstY, currentMauVien, currentStyle, currentSize);
				currShape->SetBrush(RGB(255,0,0))   ;
			}
			else
			{
				pointer = new PaintLibrary::CRectangle();
				pointer->SetType(1);
				pointer->SetData(temp_firstX, temp_firstY, temp_firstX, temp_firstY, RGB(0, 0, 0), PS_DASH, 1);
			}
		}
		break;
	}
	
	case WM_LBUTTONUP:
	{
		
		if (isTesting) {
			if (pointerSelected == FALSE)
			{
				shapes.push_back(currShape);
				isTesting = FALSE;
				temp.clear();
			}
			else
			{
				pointer2 = pointer;
				isTesting = FALSE;

			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		if (isDraw == true) {
			isClick = false;
			xLeft = 0;
			yTop = 0;
			xRight = 0;
			yBottom = 0;
			start = 0;
			break;
		}
		if (isErase == true) {
			isClick = false;
			xLeft = 0;
			yTop = 0;
			xRight = 0;
			yBottom = 0;
			start = 0;
			break;
		}

		//5, 165, 1319, 348,
		//if (yTop <= 165 | xLeft <= 5 | yBottom <= 166 | xRight >= 1320 | yTop > 511 | yBottom > 511 | xLeft >= 1320 | xRight <= 5)
		xRight = LOWORD(lParam);
		yBottom = HIWORD(lParam);
		if (yTop <= 165 | xLeft <= 5 | yBottom <= 166 | xRight >= 1320 | yTop > 511 | yBottom > 511 | xLeft >= 1320 | xRight <= 5) break;
		//xLeft += 160;
		yTop -= 165;
		//xRight += 160;
		yBottom -= 165;

		hdc = GetDC(hwndDrawArea);
		SelectObject(hdc, hPen);
		if (kBrush == 0) {
			hBrushHinh = CreateHatchBrush(HS_HORIZONTAL, currentMauNen);
		}
		else if (kBrush == 1) {
			hBrushHinh = CreateHatchBrush(HS_BDIAGONAL, currentMauNen);
		}
		else if (kBrush == 2) {
			hBrushHinh = CreateHatchBrush(HS_VERTICAL, currentMauNen);
		}
		else if (kBrush == 3) {
			hBrushHinh = CreateHatchBrush(HS_CROSS, currentMauNen);
		}
		else if (kBrush == 4) {
			hBrushHinh = CreateHatchBrush(HS_FDIAGONAL, currentMauNen);
		}
		else if (kBrush == 5) {
			hBrushHinh = CreateHatchBrush(HS_DIAGCROSS, currentMauNen);
		}
		else if (kBrush == 6) {
			hBrushHinh = CreateSolidBrush(currentMauNen);
		}
		SelectObject(hdc, hBrushHinh);
		
		if (Hinh == 0) {
			DrawDT(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 1) {
			DrawTGC(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 2) {
			DrawTGV(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 3) {
			DrawHT(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 4) {
			DrawNG(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 5) {
			DrawLG(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 6) {
			DrawMT_Right(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 7) {
			DrawMT_Left(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 8) {
			DrawMT_Down(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 9) {
			DrawMT_UP(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 10) {
			DrawNS_4(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 11) {
			DrawNS_5(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 12) {
			DrawNS_6(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 13) {
			Rectangle(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 14) {
			DrawHCN(hdc, xLeft, yTop, xRight, yBottom);
		}

		xLeft = 0;
		yTop = 0;
		xRight = 0; 
		yBottom = 0;
		isClick = false;
		ReleaseDC(hWnd, hdc);
		break;
	}
	
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			//Bat dau sua lan 8
			hPenCurCol = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			hPenCurBorCol = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			hBrushCurCol = CreateSolidBrush(currentMauNen);
			hBrushCurBorCol = CreateSolidBrush(currentMauVien);

			//Mau nen
			SelectObject(hdc, hPenCurCol);
			SelectObject(hdc, hBrushCurCol);
			TextOutA(hdc, 970, 110, "Background  Border", 19);
			TextOutA(hdc, 1020, 20, "CURRENT", 19);

			//TextOutA(hdc,300,300,"Background  Border",19);
			/*GetWindowRect(hWnd, &rect);
			DrawTextA(hdc,"Background", 12,&rect, DT_CALCRECT);*/
			Rectangle(hdc, 980, 50, 1030, 100);
			//Mau vien
			SelectObject(hdc, hPenCurBorCol);
			SelectObject(hdc, hBrushCurBorCol);
			Rectangle(hdc, 1050, 50, 1100, 100);
			//Ket thuc sua lan 8
			EndPaint(hWnd, &ps);
			setToolBox(hbrushMaunut, hWnd, color);
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
void DrawDT(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[2];
	p[0].x = left;
	p[0].y = top;
	p[1].x = right;
	p[1].y = bottom;
	Polyline(hdc, p, 2);
}
void DrawTGC(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[3];
	p[0].x = left + (right - left) / 2;
	p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 3);
}
void DrawTGV(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[3];
	p[0].x = left;
	p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 3);
}
void DrawHT(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[0].x = left + (right - left) / 2;
	p[0].y = top;

	p[1].y = p[3].y = top + (bottom - top) / 2;
	p[1].x = right;

	p[2].x = left + (right - left) / 2;
	p[2].y = bottom;

	p[3].x = left;
	Polygon(hdc, p, 4);
}
void DrawNG(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[5];
	p[0].x =  left + (right - left) / 2;
	p[0].y =  top;

	p[1].x = left;
	p[1].y = p[4].y = top + 2 * (bottom - top) / 5;

	p[2].x = left + (right - left) / 5;
	p[2].y = p[3].y = bottom;

	p[3].x = left + 4 * (right - left) / 5;

	p[4].x = right;
	Polygon(hdc, p, 5); //6->5
}
void DrawLG(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[6];
	p[0].x = p[3].x = left + (right - left) / 2;
	p[0].y = top;

	p[2].x = p[1].x = left;
	p[1].y = p[5].y = top + (bottom - top) / 4;
	p[4].x = p[5].x = right;

	p[2].y = p[4].y = top + 3 * (bottom - top) / 4;

	p[3].y = bottom;
	Polygon(hdc, p, 6);
}
void DrawMT_Right(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[7];
	p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = left;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = right;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 7);
}
void DrawMT_Left(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[7];
	p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = right;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = left;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 7);
}
void DrawMT_Down(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[7];
	p[0].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[6].y = top;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = bottom;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 7);
}
void DrawMT_UP(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[7];
	p[0].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[6].y = bottom;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = top;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 7);
}
void DrawNS_4(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[8];
	p[4].x = p[0].x = left + (right - left) / 2;
	p[0].y = top;

	p[1].x = p[3].x = left + 2 * (right - left) / 5;
	p[1].y = p[7].y = top + 2 * (bottom - top) / 5;

	p[2].x = left;
	p[2].y = p[6].y = top + (bottom - top) / 2;

	p[3].y = p[5].y = top + 3 * (bottom - top) / 5;
	p[4].y = bottom;

	p[5].x = p[7].x = left + 3 * (right - left) / 5;
	p[6].x = right;
	Polygon(hdc, p, 8);
}
void DrawNS_5(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[10];
	p[0].x = left + (right - left) / 2;
	p[0].y = top;
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
	Polygon(hdc, p, 10);
}
void DrawNS_6(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[12];
	p[6].x = p[0].x = left + (right - left) / 2;
	p[0].y = top;

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

	Polygon(hdc, p, 12);
}

void DrawHCN(HDC hdc, int left, int top, int right, int bottom) {
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
	DrawDT(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[0], &ps);

	hdc = BeginPaint(hwndShape[1], &ps);
	DrawTGC(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[1], &ps);

	hdc = BeginPaint(hwndShape[2], &ps);
	DrawTGV(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[2], &ps);

	hdc = BeginPaint(hwndShape[3], &ps);
	DrawHT(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[3], &ps);

	hdc = BeginPaint(hwndShape[4], &ps);
	DrawNG(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[4], &ps);

	hdc = BeginPaint(hwndShape[5], &ps);
	DrawLG(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[5], &ps);

	hdc = BeginPaint(hwndShape[6], &ps);
	DrawMT_Right(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[6], &ps);

	hdc = BeginPaint(hwndShape[7], &ps);
	DrawMT_Left(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[7], &ps);

	hdc = BeginPaint(hwndShape[8], &ps);
	DrawMT_Down(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[8], &ps);

	hdc = BeginPaint(hwndShape[9], &ps);
	DrawMT_UP(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[9], &ps);

	hdc = BeginPaint(hwndShape[10], &ps);
	DrawNS_4(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[10], &ps);

	hdc = BeginPaint(hwndShape[11], &ps);
	DrawNS_5(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[11], &ps);

	hdc = BeginPaint(hwndShape[12], &ps);
	DrawNS_6(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[12], &ps);

	hdc = BeginPaint(hwndShape[13], &ps);
	Rectangle(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[13], &ps);

	hdc = BeginPaint(hwndShape[14], &ps);
	DrawHCN(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[14], &ps);
	
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

	hdc = GetDC(hWnd);

	HPEN hp;
	hp = CreatePen(PS_SOLID, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hp);

	POINT point[2];
	point[0].x = 850;
	point[0].y = 50;
	point[1].x = 950;
	point[1].y = 50;
	Polyline(hdc, point, 2);

	hp = CreatePen(PS_DOT, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hp);
	point[0].x = 850;
	point[0].y = 80;
	point[1].x = 950;
	point[1].y = 80;
	Polyline(hdc, point, 2);

	hp = CreatePen(PS_DASHDOT, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hp);
	point[0].x = 850;
	point[0].y = 110;
	point[1].x = 950;
	point[1].y = 110;
	Polyline(hdc, point, 2);

	hp = CreatePen(PS_DASH, currentSize, RGB(0, 0, 0));
	SelectObject(hdc, hp);
	point[0].x = 850;
	point[0].y = 140;
	point[1].x = 950;
	point[1].y = 140;
	Polyline(hdc, point, 2);

	ReleaseDC(hWnd, hdc);
}

void setToolBox(HBRUSH hbrushMaunut, HWND hWnd, COLORREF color[]) {
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwndShape[0], &ps);
	DrawDT(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[0], &ps);

	hdc = BeginPaint(hwndShape[1], &ps);
	DrawTGC(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[1], &ps);

	hdc = BeginPaint(hwndShape[2], &ps);
	DrawTGV(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[2], &ps);

	hdc = BeginPaint(hwndShape[3], &ps);
	DrawHT(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[3], &ps);

	hdc = BeginPaint(hwndShape[4], &ps);
	DrawNG(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[4], &ps);

	hdc = BeginPaint(hwndShape[5], &ps);
	DrawLG(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[5], &ps);

	hdc = BeginPaint(hwndShape[6], &ps);
	DrawMT_Right(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[6], &ps);

	hdc = BeginPaint(hwndShape[7], &ps);
	DrawMT_Left(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[7], &ps);

	hdc = BeginPaint(hwndShape[8], &ps);
	DrawMT_Down(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[8], &ps);

	hdc = BeginPaint(hwndShape[9], &ps);
	DrawMT_UP(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[9], &ps);

	hdc = BeginPaint(hwndShape[10], &ps);
	DrawNS_4(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[10], &ps);

	hdc = BeginPaint(hwndShape[11], &ps);
	DrawNS_5(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[11], &ps);

	hdc = BeginPaint(hwndShape[12], &ps);
	DrawNS_6(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[12], &ps);

	hdc = BeginPaint(hwndShape[13], &ps);
	Rectangle(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[13], &ps);

	hdc = BeginPaint(hwndShape[14], &ps);
	DrawHCN(hdc, 5, 5, 15, 15);
	EndPaint(hwndShape[14], &ps);

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
	ReleaseDC(hWnd, hdc);
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
void OpenImage() {
	OPENFILENAME ofn;
	WCHAR szFilePath[MAX_PATH] = L"";
	WCHAR szFileTitle[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndMain;
	ofn.lpstrFilter = L"JPEG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bin";
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
	HDC hdc1 = GetDC(hwndDrawArea);
		
	if (isDraw == true && isClick == true && xLeft !=0 && yTop !=0 && x !=0 && y != 0  ) {
		
		if (start == 0) {
			start++;
			xLeft = x;
			yTop = y;
		}
		else {
			HPEN newhpen = CreatePen(PS_SOLID, currentSize, currentMauVien);
			SelectObject(hdc1, newhpen);
			DrawDT(hdc1, xLeft, yTop, x, y);
			xLeft = x;
			yTop = y;
			DeleteObject(newhpen);
		}
		
	}
	ReleaseDC(hwndDrawArea, hdc1);
	WCHAR buffer[15];
	swprintf_s(buffer, 15, L"%d x %d", x, y);
	SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);
}
void OnMouseMove2(HWND hwnd, int x, int y, UINT keyFlags)
{
	HDC hdc1 = GetDC(hwndDrawArea);

	if (isErase == true && isClick == true && xLeft != 0 && yTop != 0 && x != 0 && y != 0 && x <= 1305 && y <= 495 && x > 13 && y> 13) {

		if (start == 0) {
			start++;
			xLeft = x;
			yTop = y;
		}
		else {
			SetCursor(LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2)));
			temp_hPen = CreatePen(PS_SOLID,20, RGB(255,255,255));
			SelectObject(hdc1, temp_hPen);
			DrawDT(hdc1, xLeft, yTop, x, y);
			xLeft = x;
			yTop = y;
			DeleteObject(temp_hPen);
		}

	}
	ReleaseDC(hwndDrawArea, hdc1);
	WCHAR buffer[15];
	swprintf_s(buffer, 15, L"%d x %d", x, y);
	SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);
}


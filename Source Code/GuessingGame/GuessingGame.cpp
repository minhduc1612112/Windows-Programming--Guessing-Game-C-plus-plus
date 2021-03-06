// GuessingGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GuessingGame.h"
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <ctime>
#include<iostream>
using namespace std;

#define MAX_LOADSTRING 100
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR checkArr[] = { 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n' ,
                     'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n' };
LPCWSTR animalArr[] = { L"Lion", L"Zebra",L"Leopard", L"Hippo",L"Eagle",      //Các con vật từ 0 đến 9 tương ứng
                        L"Rhino",L"parrot",L"Vulture",L"Hedgehog",L"jellyfish",//với các bitmap1 đến bitmap10
	                    L"Tiger",L"Aligator",L"Baboon",L"Boar",L"Centipede",
						L"Chameleon",L"Cobra",L"Dog",L"Elephant",L"Fly" };
LPCWSTR messNumQues[] = { L"Câu 1", L"Câu 2:" , L"Câu 3:", L"Câu 4:", L"Câu 5:",
					      L"Câu 6:", L"Câu 7:", L"Câu 8:", L"Câu 9:", L"Câu 10:", L"" };
LPCWSTR messScores[] = { L"Điểm: 0", L"Điểm: 1", L"Điểm: 2", L"Điểm: 3", L"Điểm: 4", L"Điểm: 5" ,
					     L"Điểm: 6", L"Điểm: 7", L"Điểm: 8", L"Điểm: 9", L"Điểm: 10" };
HWND sttNumQuestion;
HWND sttQuestion;
HWND sttScores;
HWND btnChoose1;
HWND btnChoose2;
HBITMAP hbmImage;
LPCWSTR nameButton[2];
int ID;//ID là vị trí animal (từ 0 đến 9) trong animalArr[]
int question = 1;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void Random(LPCWSTR animalArr[], WCHAR checkArr[]);
void ClickButton(LPCWSTR);

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
	LoadStringW(hInstance, IDC_GUESSINGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESSINGGAME));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_GUESSINGGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GUESSINGGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 400, nullptr, nullptr, hInstance, nullptr);

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
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
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


BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	sttNumQuestion = CreateWindowEx(NULL, L"STATIC", messNumQues[0],
		WS_CHILD | WS_VISIBLE | SS_CENTER, 20, 20, 40, 40, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(sttNumQuestion, hFont, TRUE);

	sttQuestion = CreateWindowEx(NULL, L"STATIC", L"Trong hình là động vật gì?",
		WS_CHILD | WS_VISIBLE | SS_CENTER, 60, 20, 200, 40, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(sttQuestion, hFont, TRUE);

	sttScores = CreateWindowEx(NULL, L"STATIC", messScores[0],
		WS_CHILD | WS_VISIBLE | SS_CENTER, 400, 20, 60, 40, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(sttScores, hFont, TRUE);

	Random(animalArr, checkArr);

	hbmImage= LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(ID + 147));//Vì ở trong bảng Resource Symbols các IDB_BITMAP1 đến IDB_BITMAP10 
	                                                                     //có giá trị lần lượt từ 147 đến 156

	btnChoose1 = CreateWindowEx(NULL, L"BUTTON", nameButton[0],
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 280, 150, 50, hwnd,
		(HMENU)IDC_BTNCHOOSE1, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btnChoose1, hFont, TRUE);

	btnChoose2 = CreateWindowEx(NULL, L"BUTTON", nameButton[1],
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 280, 280, 150, 50, hwnd,
		(HMENU)IDC_BTNCHOOSE2, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btnChoose2, hFont, TRUE);
	
	return TRUE;
}



void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTNCHOOSE1:
		ClickButton(nameButton[0]);
		break;
	case IDC_BTNCHOOSE2:
		ClickButton(nameButton[1]);
		break;
	}
}


void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
	BITMAP bm;
	PAINTSTRUCT ps;
	HDC hdc = GetDC(hwnd);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmImage);
	GetObject(hbmImage, sizeof(bm), &bm);
	BitBlt(hdc, 90, 60, bm.bmWidth, bm.bmHeight,
		hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	EndPaint(hwnd, &ps);
}

void Random(LPCWSTR animalArr[], WCHAR checkArr[])
{
	do
	{
		srand(time(NULL));
		ID = rand() % (100); //Random số ngẫu nhiên từ 0 đến 99
		ID = ID / 10;  //Chuyển thành từ 0 đến 9
	} while (checkArr[ID] == 'y');
	checkArr[ID] = 'y';

	int IDtmp;
	do
	{
		srand(time(NULL));
		IDtmp = rand() % (100) + 100; //Random số ngẫu nhiên từ 1000 đến 1999
		IDtmp = IDtmp / 10;  //Chuyển thành từ 10 đến 19
	} while (checkArr[IDtmp] == 'y');
	checkArr[IDtmp] = 'y';

	int a = rand() % (2);//Random ngẫu nhiên 0 hoặc 1
	int b = 1 - a;

	nameButton[a] = animalArr[ID];
	nameButton[b] = animalArr[IDtmp];
}

void ClickButton(LPCWSTR nameBtn)
{
	if (question == 10)
	{
		//MessageBox(0, messScores[question], L"DONE!!!", 0); //Thông báo điểm 
		//(Lỗi không thể giải thích: Nếu thêm dòng MessageBox này thì chương trình bị crash)

		PostQuitMessage(0);//Kết thúc game
	}

	if (nameBtn == animalArr[ID])//Nếu trả lời đúng thì qua câu kế tiếp
	{
		SetWindowText(sttNumQuestion, messNumQues[question]);//Hiển thị câu hỏi kế tiếp
		SetWindowText(sttScores, messScores[question]);//Hiển thị điểm số hiện tại

		if (question <= 9)//Vì chỉ có 10 image trong đó 1 image đã load ở hàm create
			              //xuống đây chỉ được load 9 image nữa tương ứng với 9 câu hỏi còn lại
		{
			Random(animalArr, checkArr);
			hbmImage = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(ID + 147));
			SetWindowText(btnChoose1, nameButton[0]);
			SetWindowText(btnChoose2, nameButton[1]);
		}
		
		question++;
	}
	else
	{
		//MessageBox(NULL, L"Chọn sai rồi!!!", L"Thông báo", 0); 
		//MessageBox(0, messScores[question-1], L"GAME OVER!!!", 0);//Thông báo điểm 
		//(Lỗi không thể giải thích: Nếu thêm hai dòng MessageBox này thì chương trình bị crash)

		PostQuitMessage(0);//Kết thúc game
	}
	
}
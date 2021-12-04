#include"control.h"
#include<tchar.h>
#include <time.h>
static TCHAR szWndClassName[] = "WindowClass";
static TCHAR szTitle[] = "Lab1: mooving sprite";
static TCHAR szBitMap[] = "BMImage";
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HDC hDC;
LPPAINTSTRUCT ps;
static BITMAP bm;
int cx, cy;
HDC spriteImage;
HDC bckImage;


void FinalizeBackBuffer()
{
	if (hdcBack)
	{
		RestoreDC(hdcBack, -1);
		DeleteObject(hbmBack);
		DeleteDC(hdcBack);
		hdcBack = 0;
	}
}

void InitializeBackBuffer(int width, int height)
{
	HDC hdcWindow;
	hdcWindow = GetDC(hWnd);
	hdcBack = CreateCompatibleDC(hdcWindow);
	hbmBack = CreateCompatibleBitmap(hdcWindow, width, height);
	ReleaseDC(hWnd, hdcWindow);

	SaveDC(hdcBack);
	SelectObject(hdcBack, hbmBack);
}

HDC LoadBitmapDC(char* fileName)
{
	HANDLE hBitmap = LoadImageW(0, (LPWSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	int i = GetLastError();
	HDC hdc = GetDC(hWnd);
	HDC resultDC = CreateCompatibleDC(hdc);
	SelectObject(resultDC, hBitmap);
	ReleaseDC(0, hdc);

	return resultDC;
}

void Init()
{
	bckImage = LoadBitmapDC((char*)L"Background.bmp\0");
	spriteImage = LoadBitmapDC((char*)L"kasper.bmp\0");
}

void Draw()
{
	PAINTSTRUCT ps;
	FillRect(hdcBack, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	GdiTransparentBlt(hdcBack, 0, 0, 1051, 612, bckImage, 0, 0, 1436, 890, 1);
	GdiTransparentBlt(hdcBack, image.xoriginDest, image.yoriginDest, 100, 100, spriteImage, 0, 0, 100, 100, 0x00FFFFFF);
}

HANDLE hBitMap;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int LenCmd)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), 0, WndProc, 0, 0, hInstance, 0, LoadCursor(0, IDC_HAND),
		(HBRUSH)(COLOR_WINDOW + 1), NULL, (LPSTR)L"First OSaSP lab", 0
	};
	MSG msg;

	RegisterClassEx(&wcex);

	hWnd = CreateWindowEx(WS_EX_ACCEPTFILES, (LPSTR)L"First OSaSP lab\0", (LPSTR)L"Lab_1_C\0", WINDOW_STYLE,
		(GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, NULL);

	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


bool img = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	const int step = 5;
	static int wheelDelta = 0;
	static bool isShiftPressed = false;
	HDC hdc;
	PAINTSTRUCT ps;
	GetObject(hBitMap, sizeof(BITMAP), &bm);

	switch (uMsg)
	{
	case WM_CREATE:
		Init();
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);  // ширина рабочей области 
		cy = HIWORD(lParam); // высота рабочей области 
		GetClientRect(hWnd, &rcClient);
		FinalizeBackBuffer();
		InitializeBackBuffer(cx, cy);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		Draw();
		hDC = BeginPaint(hWnd, &ps);
		BitBlt(hDC, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		hdcBack, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	/*case WM_TIMER:
		GetClientRect(hWnd, &rect);
		CheckBoard(rect.right - rect.left, rect.bottom - rect.top, bm, step);
		InvalidateRect(hWnd, NULL, FALSE);*/
	case WM_KEYDOWN:
		int keyPressed;
		keyPressed = (int)wParam;
		switch (keyPressed)
		{
		case VK_LEFT:
			//Clear();
			MoveLeft();
			break;
		case VK_RIGHT:
			MoveRight();
			break;
		case VK_UP:
			//Clear();
			MoveUp();
			break;
		case VK_DOWN:
			//Clear();
			MoveDown();
			break;
		case VK_SHIFT:
			isShiftPressed = true;
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, 0, 0);
		break;
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			if (GET_KEYSTATE_WPARAM(wParam) == MK_SHIFT)
			{
				MoveRight();
			}
			else
			{
				MoveUp();
			}
		}
		else
		{
			if (GET_KEYSTATE_WPARAM(wParam) == MK_SHIFT)
			{
				MoveLeft();
			}
			else
			{
				MoveDown();
			}
		}

		InvalidateRect(hWnd, 0, 0);
		break;
	case WM_KEYUP:
		if ((int)wParam == VK_SHIFT)
			isShiftPressed = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
}
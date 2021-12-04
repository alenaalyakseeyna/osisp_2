#pragma once
#include<Windows.h>
#include <WindowsX.h>
#include <shellapi.h>
#include <rpcasync.h>

#define minY 23
#define WndHeight 610
#define minX 102
#define WndWidth 1050
#define imgWidth 100
#define imgHeight 100
#define WINDOW_STYLE (WS_VISIBLE | WS_OVERLAPPEDWINDOW) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX)
#define WINDOW_WIDTH 1065
#define WINDOW_HEIGHT 650

HDC KasperIMG;
HBITMAP hbmBack;
//HDC spriteImage;
//HDC bckImage;
HDC hdcBack;
HWND hWnd;
HDC winDC;
RECT rcClient;
int step = 10;

int pos_x1 = 0, pos_y1 = 0, pos_x2 = 0,pos_y2 = 0;
int sideLen = 60;


//int posX = 0, posY = 0;
int horisontDir = 1;
int verticalDir = 1;

typedef struct _Image
{
	int xoriginDest;
	int yoriginDest;
} Image;

Image image = { minX, minY };

void CheckWindowSize(int wndW, int wndH, int width, int height)
{
	int res = wndW - width;
	if (pos_x1 > res && wndW > width)
		pos_x1 = res;
	if (res < 0)
		pos_x1 = 0;
	res = wndH - height;
	if (pos_y1 > res && wndH > height)
		pos_y1 = res;
	if (res < 0)
		pos_y1 = 0;
}


//Try to do rebound
//void CheckBoard(int WndWidth, int WndHeight, BITMAP bm, int step)
//{
//	if (horisontDir < 0)
//	{
//		if (pos_x >= WndWidth - bm.bmWidth)
//		{
//			horisontDir *= -1;
//			pos_x += step * horisontDir;
//		}
//	}
//	else
//	{
//		if (pos_x < 0)
//		{
//			horisontDir *= -1;
//			pos_x += step * horisontDir;
//		}
//	}
//	if (verticalDir < 0)
//	{
//		if (pos_y >= WndHeight - bm.bmHeight)
//		{
//			verticalDir *= -1;
//			pos_y += step * verticalDir;
//		}
//	}
//	else
//	{
//		if (pos_y <= 0)
//		{
//			verticalDir *= -1;
//			pos_y += step * verticalDir;
//		}
//	}
//}


void MoveUp()
{
	if (image.yoriginDest > 0)
	{
		if (image.yoriginDest > step)
			image.yoriginDest -= step;
		else
			image.yoriginDest -= image.yoriginDest;
	}
	else
	{
		image.yoriginDest += 30;
	}

}

void MoveLeft()
{
	if (image.xoriginDest > 0)
	{
		if (image.xoriginDest > step)
			image.xoriginDest -= step;
		else
			image.xoriginDest -= image.xoriginDest;
	}
	else
	{
		image.xoriginDest += 30;
	}

}

void MoveRight()
{
	if (image.xoriginDest < WndWidth - imgWidth)
	{
		if (WndWidth > imgWidth)
		{
			if (image.xoriginDest < WndWidth - imgWidth - step)
				image.xoriginDest += step;
			else
				image.xoriginDest += (WndWidth - imgWidth) - image.xoriginDest;
		}
	}
	else
	{
		image.xoriginDest -= 30;
	}

}

void MoveDown()
{
	if (image.yoriginDest < WndHeight - imgHeight)
	{
		if (WndHeight > imgHeight) {
			if (image.yoriginDest < WndHeight - imgHeight - step)
				image.yoriginDest += step;
			else
				image.yoriginDest += (WndHeight - imgHeight) - image.yoriginDest;
		}
	}
	else
	{
		image.yoriginDest -= 30;
	}

}


//void Clear()
//{
//	winDC = GetDC(hWnd);
//	bmpDC = CreateCompatibleDC(winDC);
//	GetClientRect(hWnd, &rect);
//	hbmBack = CreateCompatibleBitmap(winDC, rect.right - rect.left, rect.bottom - rect.top);
//	ReleaseDC(hWnd, winDC);
//
//	SaveDC(bmpDC);
//	SelectObject(bmpDC, hbmBack);
//}

//void Draw(BITMAP bm, HANDLE hBitMap, HDC KasperIMG)
//{
//	// MB it's like a joke, but my dooble buferization
//	// do not wark at all, I've took this example from
//	// Alesya's program
//	// tooday is the end of october, and I have big problem
//	// press F ... pleaase
//	RECT clientRect;
//
//	PAINTSTRUCT ps;
//
//	RECT rect{ pos_x1, pos_y1, bm.bmWidth, bm.bmHeight };
//	//FillRect(bmpDC, &ps.rcPaint, /*(HBRUSH)(COLOR_WINDOW + 1)*/WHITE_BRUSH);
//	//GdiTransparentBlt(bmpDC, 0, 0, 100, 100, hbmBack, 0, 0, 100, 100, 0xffffff); I killed you
//	GdiTransparentBlt(bmpDC, pos_x1, pos_y1, 100, 100, KasperIMG, 0, 0, 100, 100, 0x00FFFFFF);
//
//	/*if (bmpDC)
//	{
//		RestoreDC(bmpDC, -1);
//		DeleteObject(hbmBack);
//		DeleteDC(bmpDC);
//		bmpDC = 0;
//	}*/
//
//	//RECT windowSize;
//	//GetClientRect(hWnd, &clientRect);
//	//HBITMAP oldBmp = static_cast<HBITMAP>(SelectObject(bmpDC, hBitMap));
//	//BitBlt(winDC, pos_x1, pos_y1, bm.bmWidth, bm.bmHeight, bmpDC, 0, 0, SRCCOPY);
//	//SelectObject(bmpDC, oldBmp);
//	//DeleteDC(bmpDC);
//
//	//
//
//	//EndPaint(hWnd, &ps);
//}

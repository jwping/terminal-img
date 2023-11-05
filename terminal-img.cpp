#include <stdio.h>
#include <windows.h>
#include <string>
#include <atlimage.h>

#include "terminal-img.h"


char* imgPath = { 0 };
bool windowDESTROY = 0;

LRESULT __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	CImage			image;

	switch (msg)
	{
	case WM_PAINT:
		PAINTSTRUCT     ps;
		HDC             hdc;
		BITMAP			bitmap;
		HBITMAP			hBitmap;
		HDC             hdcMem;

		// hBitmap = (HBITMAP)LoadImage(wc.hInstance, "1.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		image.Load(imgPath);
		hBitmap = image.Detach();

		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		SelectObject(hdcMem, hBitmap);
		BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		DeleteDC(hdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		windowDESTROY = true;
		break;
	default:
		// printf(".");
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
};


// windowName: window title
// windowX: X-axis offset
// windowY: Y-axis offset
// windowWidth: Window Width
// windowHeight: window Height
// img_path: Image Path
int PopImg(const char * windowName, int windowX, int windowY, int windowWidth, int windowHeight, const char *img_path) {
	// const char* const windowClass = "terminal-img";

	imgPath = (char *)img_path;

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	/* Win 3.x */
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);

	// wc.hIcon = NULL;
	// wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	// wc.hCursor = LoadCursor(0, IDC_ARROW);
	// wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// wc.lpszMenuName = 0;

	// Name the class name with the window title
	// wc.lpszClassName = windowClass;
	wc.lpszClassName = windowName;

	/* Win 4.0 */
	// wc.hIconSm = NULL;
	// wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

	if (RegisterClassEx(&wc))
	{

		// Registered Class Name Reuse Title Name
		// HWND window = CreateWindowEx(0, windowName, windowName,
		// 	WS_OVERLAPPEDWINDOW, windowX, windowY,
		// 	windowWidth, windowHeight, 0, 0, NULL, 0);

		// Registered Class Name Reuse Title Name
		HWND window = CreateWindow(windowName, windowName,
			WS_OVERLAPPEDWINDOW, windowX, windowY,
			windowWidth, windowHeight, 0, 0, GetModuleHandle(0), 0);

		if (window)
		{
			ShowWindow(window, SW_SHOWDEFAULT);
			UpdateWindow(window);

			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0))
			{
				if (windowDESTROY) {
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return 0;
		}
	}

	return 1;
}

void hideTheCursor() {
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
		cciCursor.bVisible = FALSE;
		SetConsoleCursorInfo(hStdOut, &cciCursor);
	}
}
void showTheCursor() {
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
		cciCursor.bVisible = TRUE;
		SetConsoleCursorInfo(hStdOut, &cciCursor);
	}
}

// img_path: Image Path
// offsetX: X-axis offset
// offsetY: Y-axis offset
int ConsoleImg(const char* img_path, int offsetX, int offsetY) {
	imgPath = (char *)img_path;

	int result;
	HWND  hwnd;
	HDC   hdc;
	HFONT hfont;
	HBITMAP hbm;
	HDC hdcBits;
	BITMAP bm;
	CImage image;

	system("color F0");
	// system("color 07");
	system("cls");
	hideTheCursor();
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);

	
	image.Load(imgPath);
	hbm = image.Detach();

	// hbm = LoadBitmap(GetModuleHandle(NULL), "1.png");
	// hbm = (HBITMAP)LoadImage(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (hbm) {
		

		hdcBits = CreateCompatibleDC(hdc);
		GetObject(hbm, sizeof(BITMAP), &bm);
		SelectObject(hdcBits, hbm);
		BitBlt(hdc, offsetX, offsetY, bm.bmWidth, bm.bmHeight, hdcBits, 0, 0, SRCCOPY);
		DeleteDC(hdcBits);
		DeleteObject(hbm);

		// Waiting for user confirmation
		getchar();
		
		result = 0;
	}
	else {
		result = 1;
	}

	system("color 07");
	system("cls");
	showTheCursor();

	return result;
}

int main()
{
	if (PopImg("terminal-img", 0, 0, 500, 500, "1.gif") != 0) {
		printf("Picture pop-up failed!\n");
	}

	if (ConsoleImg("1.gif", 0, 0) != 0) {
		printf("Console image output failed!\n");
	}
	return 0;
}
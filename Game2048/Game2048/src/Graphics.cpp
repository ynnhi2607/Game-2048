#include "Graphics.h"
void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD c = { x,y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, c);
}
void TextColor(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
void SetColor(int x)
{
	if (x == 2 || x == 4) TextColor(7);
	else if (x == 8) TextColor(14);
	else if (x == 16) TextColor(6);
	else if (x == 32) TextColor(10);
	else if (x == 64) TextColor(11);
	else if (x == 128) TextColor(12);
	else if (x == 256) TextColor(13);
	else if (x == 512) TextColor(9);
	else if (x > 512) TextColor(1);
}
void WordArt(string chu, int startX, int startY)
{
	TextColor(15);
	int x = startX;
	int y = startY;
	for (char ch : chu)
	{
		if (ch == '\n')
		{
			// Điều chỉnh tọa độ xuống dòng mới
			x = startX;
			++y;
		}
		else
		{
			// Di chuyển con trỏ đến tọa độ và in ký tự
			gotoXY(x, y);
			std::cout << ch;
			++x;
		}
	}
}
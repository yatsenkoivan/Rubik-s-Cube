#pragma once
#include <windows.h>

enum Colors {
	white = 7, blue=1, red=4, green=2, orange=5, /*pink instead*/ yellow=6, null = 0
};

void SetColor(Colors color=null) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color*16 + color);
}
void RestoreColor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
}
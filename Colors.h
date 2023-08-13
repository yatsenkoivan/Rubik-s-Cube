#pragma once
#include <windows.h>

enum Colors {
	white = 15, blue=9, red=12, green=10, orange=13, /*pink instead*/ yellow=14
};

void SetColor(Colors color) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
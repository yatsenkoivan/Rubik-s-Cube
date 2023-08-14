#pragma once
#include <windows.h>

namespace Cursor
{
	void set(SHORT x=0, SHORT y=0) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = { x, y };
		SetConsoleCursorPosition(h, pos);
	}
}
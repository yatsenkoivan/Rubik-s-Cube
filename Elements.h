#pragma once
#include "Colors.h"

struct Element
{
	static int size_x;
	static int size_y;
	Colors color;
	Element(Colors color) : color{ color } {}
};
int Element::size_x = 5;
int Element::size_y = 3;
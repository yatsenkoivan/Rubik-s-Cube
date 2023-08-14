#pragma once
#include "Elements.h"
#include "Cursor.h"
#include <iostream>

struct Side
{
	static int size;
	static int gap;

	Element*** elements;

	Side(Colors color) {
		elements = new Element * *[size];
		for (int row = 0; row < size; row++)
		{
			elements[row] = new Element * [size];
			for (int col = 0; col < size; col++)
			{
				elements[row][col] = new Element(color);
			}
		}
	}
	void Show(int start_x, int start_y)
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				int x = col * Element::size_x + col * gap;
				int y = row * Element::size_y + row * gap;
				SetColor(elements[row][col]->color);
				for (int i = 0; i < Element::size_y; i++)
				{
					Cursor::set(x + start_x, y + start_y + i);
					for (int j=0; j<Element::size_x; j++) std::cout << '.';
				}
			}
		}
		RestoreColor();
		//FIX
		for (int i = 0; i < size * Element::size_y + (size-1)*gap; i++)
		{
			Cursor::set(start_x + size * Element::size_x + (size - 1) * gap, start_y + i);
			std::cout << '.';
		}
	}
	~Side()
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				delete elements[row][col];
			}
			delete[] elements[row];
		}
		delete[] elements;
	}
};
int Side::size = 3;
int Side::gap = 1;
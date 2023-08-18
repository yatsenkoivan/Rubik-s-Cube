#pragma once
#include "Elements.h"
#include "Cursor.h"
#include <iostream>


struct Side;


struct Cursor
{
	static int x;
	static int y;
	static const char symbol = '#';
	static const char move_symbol = 'O';
	static bool move;
	static Side* side;
};
int Cursor::x = 0;
int Cursor::y = 0;
Side* Cursor::side = nullptr;
bool Cursor::move = false;


struct Side
{
	static int size;
	static int gap;

	Element*** elements;

	Side* left;
	Side* up;
	Side* right;
	Side* down;

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
		left = nullptr;
		up = nullptr;
		right = nullptr;
		down = nullptr;
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
					SetCursor(x + start_x, y + start_y + i);
					for (int j = 0; j < Element::size_x; j++)
					{
						if (this == Cursor::side && row == Cursor::y && col == Cursor::x)
						{
							if (Cursor::move) std::cout << Cursor::move_symbol;
							else std::cout << Cursor::symbol;
						}
						else std::cout << ' ';
					}
				}
			}
		}
		SetColor();
		//FIX
		for (int i = 0; i < size * Element::size_y + (size - 1) * gap; i++)
		{
			SetCursor(start_x + size * Element::size_x + (size - 1) * gap, start_y + i);
			std::cout << '.';
		}
	}
	void horizontal_reverse()
	{
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size/2; col++)
			{
				std::swap(elements[row][col], elements[row][size - col - 1]);
			}
		}
	}
	void vertical_reverse()
	{
		for (int row = 0; row < size/2; row++)
		{
			for (int col = 0; col < size; col++)
			{
				std::swap(elements[row][col], elements[size - row - 1][col]);
			}
		}
	}
	void Rotate(bool clockwise = true)
	{
		Element*** temp = new Element ** [Side::size];
		for (int row = 0; row < Side::size; row++)
		{
			temp[row] = new Element * [Side::size];
			for (int col = 0; col < Side::size; col++)
			{
				temp[row][col] = elements[row][col];
			}
		}
		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{

				if (clockwise)
				{
					temp[row][col] = elements[size - col - 1][row];
				}
				else
				{
					temp[row][col] = elements[col][size - row - 1];
				}

			}
		}
		for (int row = 0; row < Side::size; row++)
		{
			for (int col = 0; col < Side::size; col++)
			{
				elements[row][col] = temp[row][col];
			}
			delete[] temp[row];
		}
		delete[] temp;
	}
};
int Side::size = 3;
int Side::gap = 1;
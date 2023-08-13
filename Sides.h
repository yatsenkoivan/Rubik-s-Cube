#pragma once
#include "Elements.h"

struct Side
{
	Element*** elements;
	Side* left;
	Side* right;
	Side* up;
	Side* down;
	int size;
	Side(int size, Colors color) : size{size}
	{
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
		right = nullptr;
		up = nullptr;
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
};
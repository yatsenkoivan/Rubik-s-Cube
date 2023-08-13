#pragma once
#include "Sides.h"

class Cube
{
	private:
		static int height;
		static int length;
		static int width;
		static int gap;
		static int sides_amount;

		Side** sides;
		Side* current_size;

};
int Cube::height = 3;
int Cube::length = 3;
int Cube::width = 3;
int Cube::gap = 1;
int Cube::sides_amount = 6;

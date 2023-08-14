#pragma once
#include "Sides.h"
#include <conio.h>

class Cube
{
	private:
		static int sides_gap;
		static int offset_x;
		static int offset_y;

		Side** sides;

	public:
		Cube()
		{
			sides = new Side * [6];
			sides[0] = new Side(Colors::blue);
			sides[1] = new Side(Colors::white);
			sides[2] = new Side(Colors::red);
			sides[3] = new Side(Colors::orange);
			sides[4] = new Side(Colors::green);
			sides[5] = new Side(Colors::yellow);
		}
		~Cube()
		{
			for (int side = 0; side < 6; side++)
			{
				delete sides[side];
			}
			delete[] sides;
		}
		void Show()
		{
			int x = offset_x;
			int y = offset_y;

			int next_y = sides_gap + Side::size * Element::size_y + (Side::size - 1) * Side::gap;
			int next_x = sides_gap + Side::size * Element::size_x + (Side::size - 1) * Side::gap;

			sides[2]->Show(x + next_x,
						   y);
			sides[3]->Show(x + next_x,
						   y + next_y*2);

			y += next_y;

			sides[0]->Show(x,
						   y);
			x += next_x;

			sides[1]->Show(x,
						   y);
			x += next_x;

			sides[4]->Show(x,
						   y);
			x += next_x;
			sides[5]->Show(x,
						   y);

		}
		void Start()
		{
			while (true)
			{
				Show();
				_getch();
			}
		}
};
int Cube::sides_gap = 2;
int Cube::offset_x = 2;
int Cube::offset_y = 2;

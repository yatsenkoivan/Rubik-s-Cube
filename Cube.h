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


			//REFERENCES
			sides[0]->left = sides[5];
			sides[0]->up = sides[2];
			sides[0]->right = sides[1];
			sides[0]->down = sides[3];

			sides[1]->left = sides[0];
			sides[1]->up = sides[2];
			sides[1]->right = sides[4];
			sides[1]->down = sides[3];

			sides[2]->left = sides[0];
			sides[2]->up = sides[3];
			sides[2]->right = sides[4];
			sides[2]->down = sides[1];

			sides[3]->left = sides[0];
			sides[3]->up = sides[1];
			sides[3]->right = sides[4];
			sides[3]->down = sides[2];

			sides[4]->left = sides[1];
			sides[4]->up = sides[2];
			sides[4]->right = sides[5];
			sides[4]->down = sides[3];

			sides[5]->left = sides[4];
			sides[5]->up = sides[2];
			sides[5]->right = sides[0];
			sides[5]->down = sides[3];


			Cursor::side = sides[1];
			Cursor::x = Side::size/2;
			Cursor::y = Side::size/2;


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
		void Press(char key)
		{
			switch (key)
			{
				case 'a':
				case 'A':
					if (Cursor::x - 1 >= 0) Cursor::x--;
					else
					{
						Cursor::side = Cursor::side->left;
						Cursor::x = Side::size-1;
					}
					break;
				case 'w':
				case 'W':
					if (Cursor::y - 1 >= 0) Cursor::y--;
					else
					{
						Cursor::side = Cursor::side->up;
						Cursor::y = Side::size-1;
					}
					break;
				case 'd':
				case 'D':
					if (Cursor::x + 1 < Side::size) Cursor::x++;
					else
					{
						Cursor::side = Cursor::side->right;
						Cursor::x = 0;
					}
					break;
				case 's':
				case 'S':
					if (Cursor::y + 1 < Side::size) Cursor::y++;
					else
					{
						Cursor::side = Cursor::side->down;
						Cursor::y = 0;
					}
					break;
				case 'x':
				case 'X':
					if (Cursor::move) Cursor::move = false;
					else Cursor::move = true;
					break;
				case 'r':
				case 'R':
					system("cls");
					break;
			}
		}
		void Start()
		{
			char key;
			while (true)
			{
				Show();
				key = _getch();
				Press(key);
			}
		}
};
int Cube::sides_gap = 2;
int Cube::offset_x = 2;
int Cube::offset_y = 2;

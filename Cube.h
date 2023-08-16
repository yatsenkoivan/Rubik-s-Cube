#pragma once
#include "Sides.h"
#include <conio.h>

enum Directions
{
	left, up, right, down
};

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
			sides[2]->up = sides[5];
			sides[2]->right = sides[4];
			sides[2]->down = sides[1];

			sides[3]->left = sides[0];
			sides[3]->up = sides[1];
			sides[3]->right = sides[4];
			sides[3]->down = sides[5];

			sides[4]->left = sides[1];
			sides[4]->up = sides[2];
			sides[4]->right = sides[5];
			sides[4]->down = sides[3];

			sides[5]->left = sides[4];
			sides[5]->up = sides[3];
			sides[5]->right = sides[0];
			sides[5]->down = sides[2];


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
		void Move(Directions direction)
		{
			Side* first = Cursor::side;
			Side* current = Cursor::side;

			Element** temp = new Element * [Side::size];
			for (int i = 0; i < Side::size; i++)
			{
				switch (direction)
				{
					case Directions::left:
					case Directions::right:
						temp[i] = first->elements[Cursor::y][i];
						break;
					case Directions::up:
					case Directions::down:
						temp[i] = first->elements[i][Cursor::x];
						break;
				}
			}

			do
			{
				switch (direction)
				{
					case Directions::left:
						for (int i = 0; i < Side::size; i++)
						{
							if (current->right == first)
								current->elements[Cursor::y][i] = temp[i];
							else
								current->elements[Cursor::y][i] = current->right->elements[Cursor::y][i];
						}
						current = current->right;
						break;
					case Directions::up:
						for (int i = 0; i < Side::size; i++)
						{
							if (current->down == first)
								current->elements[i][Cursor::x] = temp[i];
							else
								current->elements[i][Cursor::x] = current->down->elements[i][Cursor::x];
						}
						current = current->down;
						break;
					case Directions::right:
						for (int i = 0; i < Side::size; i++)
						{
							if (current->left == first)
								current->elements[Cursor::y][i] = temp[i];
							else
								current->elements[Cursor::y][i] = current->left->elements[Cursor::y][i];
						}
						current = current->left;
						break;
					case Directions::down:
						for (int i = 0; i < Side::size; i++)
						{
							if (current->up == first)
								current->elements[i][Cursor::x] = temp[i];
							else
								current->elements[i][Cursor::x] = current->up->elements[i][Cursor::x];
						}
						current = current->up;
						break;
				}
			} while (current != first);
			delete[] temp;
		}
		void Press(char key)
		{
			switch (key)
			{
				case 'a':
				case 'A':
					//move to left
					if (Cursor::move)
					{
						if (Cursor::y == 0) Cursor::side->up->Rotate();
						if (Cursor::y == Side::size - 1) Cursor::side->down->Rotate(false);
						Move(Directions::left);
						break;
					}
					if (Cursor::x - 1 >= 0) Cursor::x--;
					else
					{
						Cursor::side = Cursor::side->left;
						Cursor::x = Side::size-1;
					}
					break;
				case 'w':
				case 'W':
					//move to up
					if (Cursor::move)
					{
						if (Cursor::x == 0) Cursor::side->left->Rotate(false);
						if (Cursor::x == Side::size-1) Cursor::side->right->Rotate();
						Move(Directions::up);
						break;
					}
					if (Cursor::y - 1 >= 0) Cursor::y--;
					else
					{
						Cursor::side = Cursor::side->up;
						Cursor::y = Side::size-1;
					}
					break;
				case 'd':
				case 'D':
					//move to right
					if (Cursor::move)
					{
						if (Cursor::y == 0) Cursor::side->up->Rotate(false);
						if (Cursor::y == Side::size - 1) Cursor::side->down->Rotate();
						Move(Directions::right);
						break;
					}
					if (Cursor::x + 1 < Side::size) Cursor::x++;
					else
					{
						Cursor::side = Cursor::side->right;
						Cursor::x = 0;
					}
					break;
				case 's':
				case 'S':
					//move to down
					if (Cursor::move)
					{
						if (Cursor::x == 0) Cursor::side->left->Rotate();
						if (Cursor::x == Side::size - 1) Cursor::side->right->Rotate(false);
						Move(Directions::down);
						break;
					}
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

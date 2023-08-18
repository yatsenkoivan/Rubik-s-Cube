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
			//yellow side fix
			if (direction == Directions::up || direction == Directions::down)
			{
				sides[5]->horizontal_reverse();
				sides[5]->vertical_reverse();
			}
			if (Cursor::side == sides[5])
				Cursor::x = Side::size - Cursor::x - 1;


			//vertical fix (green & blue)
			if ((Cursor::side == sides[0] || Cursor::side == sides[4])
				&& (direction == Directions::up || direction == Directions::down))
			{
				//red
				if (Cursor::side == sides[0])
					sides[2]->Rotate(false);
				else
					sides[2]->Rotate();
				sides[2]->down = Cursor::side;
				sides[2]->up = (Cursor::side == sides[0] ? sides[4] : sides[0]);
				//orange
				if (Cursor::side == sides[0])
					sides[3]->Rotate();
				else
					sides[3]->Rotate(false);
				sides[3]->down = sides[2]->up;
				sides[3]->up = sides[2]->down;
				//opposite side
				(Cursor::side == sides[0] ? sides[4] : sides[0])->horizontal_reverse();
				(Cursor::side == sides[0] ? sides[4] : sides[0])->vertical_reverse();
				if (Cursor::side == sides[0])
				{
					sides[4]->up = sides[0]->down;
					sides[4]->down = sides[0]->up;
				}
				if (Cursor::side == sides[4])
				{
					sides[0]->up = sides[4]->down;
					sides[0]->down = sides[4]->up;
				}
			}
			//horizontal fix (red & orange)
			if ((Cursor::side == sides[2] || Cursor::side == sides[3])
				&& (direction == Directions::left || direction == Directions::right))
			{
				//blue
				if (Cursor::side == sides[3])
					sides[0]->Rotate(false);
				else
					sides[0]->Rotate();
				sides[0]->right = Cursor::side;
				sides[0]->left = (Cursor::side == sides[2] ? sides[3] : sides[2]);
				//green
				if (Cursor::side == sides[3])
					sides[4]->Rotate();
				else
					sides[4]->Rotate(false);
				sides[4]->right = sides[0]->left;
				sides[4]->left = sides[0]->right;
				//opposite side
				(Cursor::side == sides[2] ? sides[3] : sides[2])->horizontal_reverse();
				(Cursor::side == sides[2] ? sides[3] : sides[2])->vertical_reverse();
				if (Cursor::side == sides[2])
				{
					sides[3]->right = sides[2]->left;
					sides[3]->left = sides[2]->right;
				}
				if (Cursor::side == sides[3])
				{
					sides[2]->right = sides[3]->left;
					sides[2]->left = sides[3]->right;
				}
			}


			Element*** temp = new Element * *[Side::size];
			for (int row = 0; row < Side::size; row++)
			{
				temp[row] = new Element * [Side::size];
				for (int col = 0; col < Side::size; col++)
				{
					temp[row][col] = Cursor::side->elements[row][col];
				}
			}
			Side* first = Cursor::side;
			Side* current = first;


			for (int _side = 0; _side < 4; _side++)
			{
				for (int i = 0; i < Side::size; i++)
				{
					if (direction == Directions::up)
					{
						if (current == first->up)
							current->elements[i][Cursor::x] = temp[i][Cursor::x];
						else
							current->elements[i][Cursor::x] = current->down->elements[i][Cursor::x];
					}
					if (direction == Directions::down)
					{
						if (current == first->down)
							current->elements[i][Cursor::x] = temp[i][Cursor::x];
						else
							current->elements[i][Cursor::x] = current->up->elements[i][Cursor::x];
					}
					if (direction == Directions::left)
					{
						if (current == first->left)
							current->elements[Cursor::y][i] = temp[Cursor::y][i];
						else
							current->elements[Cursor::y][i] = current->right->elements[Cursor::y][i];
					}
					if (direction == Directions::right)
					{
						if (current == first->right)
							current->elements[Cursor::y][i] = temp[Cursor::y][i];
						else
							current->elements[Cursor::y][i] = current->left->elements[Cursor::y][i];
					}
				}
				if (direction == Directions::up)
					current = current->down;
				if (direction == Directions::down)
					current = current->up;
				if (direction == Directions::left)
					current = current->right;
				if (direction == Directions::right)
					current = current->left;
			}


			//yellow side fix
			if (direction == Directions::up || direction == Directions::down)
			{
				sides[5]->horizontal_reverse();
				sides[5]->vertical_reverse();
			}
			if (Cursor::side == sides[5])
				Cursor::x = Side::size - Cursor::x - 1;

			//vertical fix (green & blue)
			if ((Cursor::side == sides[0] || Cursor::side == sides[4])
				&& (direction == Directions::up || direction == Directions::down))
			{
				//red
				if (Cursor::side == sides[0])
					sides[2]->Rotate();
				else
					sides[2]->Rotate(false);
				sides[2]->down = sides[1];
				sides[2]->up = sides[5];
				//orange
				if (Cursor::side == sides[0])
					sides[3]->Rotate(false);
				else
					sides[3]->Rotate();
				sides[3]->down = sides[5];
				sides[3]->up = sides[1];
				//opposite side
				(Cursor::side == sides[0] ? sides[4] : sides[0])->horizontal_reverse();
				(Cursor::side == sides[0] ? sides[4] : sides[0])->vertical_reverse();
				if (Cursor::side == sides[0])
				{
					sides[4]->up = sides[0]->up;
					sides[4]->down = sides[0]->down;
				}
				if (Cursor::side == sides[4])
				{
					sides[0]->up = sides[4]->up;
					sides[0]->down = sides[4]->down;
				}
			}
			//horizontal fix (red & orange)
			if ((Cursor::side == sides[2] || Cursor::side == sides[3])
				&& (direction == Directions::left || direction == Directions::right))
			{
				//blue
				if (Cursor::side == sides[3])
					sides[0]->Rotate();
				else
					sides[0]->Rotate(false);
				sides[0]->right = sides[1];
				sides[0]->left = sides[5];
				//green
				if (Cursor::side == sides[3])
					sides[4]->Rotate(false);
				else
					sides[4]->Rotate();
				sides[4]->right = sides[5];
				sides[4]->left = sides[1];
				//opposite side
				(Cursor::side == sides[2] ? sides[3] : sides[2])->horizontal_reverse();
				(Cursor::side == sides[2] ? sides[3] : sides[2])->vertical_reverse();
				if (Cursor::side == sides[2])
				{
					sides[3]->right = sides[2]->right;
					sides[3]->left = sides[2]->left;
				}
				if (Cursor::side == sides[3])
				{
					sides[2]->right = sides[3]->right;
					sides[2]->left = sides[3]->left;
				}
			}

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

#include <iostream>
#include <windows.h>

#include <iomanip>
#include <stdlib.h>
using namespace std;
#define map_width  30
#define map_height 25

//Function declaration
void initialise();


class Map_Handler
{
private:
	char map_info[map_height][map_width];

public:
	Map_Handler()
	{
	}
	void initialise() //Fill all the empty tiles with '.'
	{
		for (int i = 0; i < map_width; i++)
		{
			for (int j = 0; j < map_height; j++)
			{
				set_map_char(i, j, '.');
			}
		}
	}
	void set_map_char(short x_coord, short y_coord, char map_symbol)
	{
		map_info[y_coord][x_coord] = map_symbol;
	}
	
	char get_map_char(short x_coord, short y_coord)
	{
		return map_info[y_coord][x_coord];
	}

};

class Entity
{
protected:
	char map_symbol;
	short x_coord;
	short y_coord;
	short x_previous_visual;
	short y_previous_visual;
	bool movement_visual_change = false;
public:
	Entity(short x_in, short y_in, char map_symbol_in)
	{
		x_coord = x_in;
		y_coord = y_in;
		x_previous_visual = x_in;
		y_previous_visual = y_in;
		map_symbol = map_symbol_in;
	}
	void set_coords(short x_in, short y_in)
	{
		//Updates the previous position only once that was output by the renderer for erasure of its icon.
		/*if (movement_visual_change == true)
		{
			x_previous_visual = x_coord;
			y_previous_visual = y_coord;
			movement_visual_change = false;
		}*/
		x_previous_visual = x_coord;
		y_previous_visual = y_coord;
		x_coord = x_in;
		y_coord = y_in;
	}

	void move(short x_mov, short y_mov, Map_Handler m)
	{
		int x_new = x_coord + x_mov;
		int y_new = y_coord + y_mov;

		bool within_x_bounds = (0 <= x_new and x_new < map_width);
		bool within_y_bounds = (0 <= y_new and y_new < map_height);

		bool is_wall = m.get_map_char(x_new, y_new) == 'W';

		bool x_valid = (within_x_bounds and !is_wall);
		bool y_valid = (within_y_bounds and !is_wall);

		//Ternary operators to check whether the entity is going to move out of bounds
		x_mov = x_valid ? x_mov : 0;
		y_mov = y_valid ? y_mov : 0;

		set_coords(x_coord + x_mov, y_coord + y_mov);
	}


	
	void set_movement_visual_change(bool b)
	{
		movement_visual_change = b;
	}

	short get_x_coord()
	{
		return x_coord;
	}

	short get_y_coord()
	{
		return y_coord;
	}

	short get_x_prev_visual_coord()
	{
		return x_previous_visual;
	}

	short get_y_prev_visual_coord()
	{
		return y_previous_visual;
	}

	bool get_movement_visual_change()
	{
		return movement_visual_change;
	}

	char get_map_symbol()
	{
		return map_symbol;
	}
};

class Player : public Entity
{
private:
	bool last_moved_horizontal = false;
public:
	Player(short x_in, short y_in) : Entity(x_in, y_in, 'P')
	{
	}
	void input_to_movement(Map_Handler m)
	{
		int x_move = 0;
		int y_move = 0;

		if (GetAsyncKeyState('W'))
		{
			y_move += -1;
		}

		if (GetAsyncKeyState('A'))
		{
			x_move += -1;
		}

		if (GetAsyncKeyState('S'))
		{
			y_move += 1;
		}

		if (GetAsyncKeyState('D'))
		{
			x_move += 1;
		}

		move(x_move, y_move, m);

	}
	void move(short x_mov, short y_mov, Map_Handler m)
	{
		if (x_mov and y_mov) //If the player wants to move both horizontally and vertically:
			//alternate between the two.
		{
			if (last_moved_horizontal)
			{
				Entity::move(0, y_mov, m);
				last_moved_horizontal = false;
			}
			else
			{
				Entity::move(x_mov, 0, m);
				{
					last_moved_horizontal = true;
				}
			}
		}
		else if(x_mov or y_mov) //If one of the buttons are pressed
		{
			Entity::move(x_mov, y_mov, m);
			last_moved_horizontal = x_mov; //Only one or the other can have a value now, so the value of one indicates the other.
		}
	}
};
class Renderer
{
private:
	HANDLE Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	short map_element_spacing = 2;
	COORD origin = { 0,0 };
	
public:
	Renderer()
	{
	}
	
	void initialise()
	{
		CONSOLE_CURSOR_INFO c;
		c.dwSize = 100;
		c.bVisible = false;
		SetConsoleCursorInfo(Screen, &c);
	}

	void output(Entity &e)
	{
		/*if (e.get_movement_visual_change() == false)
		{
			fill_char(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
			fill_char(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
			e.set_movement_visual_change(true);
		}*/
		fill_char(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
		fill_char(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
	}

	void fill_char(short x_coord, short y_coord, char character)
	{
		COORD position = { (short)(x_coord * map_element_spacing), y_coord };
		SetConsoleCursorPosition(Screen, position); //Move cursor to a specific position on screen
		cout << character;
		SetConsoleCursorPosition(Screen, origin);
	}

	void output(Map_Handler m)
	{
		system("cls");

		for (int j = 0; j < map_height; j++) //For each row
		{
			for (int i = 0; i < map_width; i++) //For each column
			{
				cout << m.get_map_char(i,j) << setw(map_element_spacing); //Output the character stored
			}
			cout << "\n"; //Start a new line
		}
	}

	
	
};

Renderer r;
Map_Handler m;

//Entity Test = Entity(0, 0, 'T');
//Entity Test2 = Entity(2, 2, 'E');
Player Player_Obj = Player(4, 4);


int main()
{
	initialise();
	while (true)
	{
		
		Player_Obj.input_to_movement(m);
		
		r.output(Player_Obj);
		

		//r.output(p);
		

		Sleep(100);
	}

	return 0;
}

void initialise()
{
	r.initialise();
	m.initialise();
	
	m.set_map_char(20, 20, 'W');
	m.set_map_char(21, 20, 'W');
	m.set_map_char(23, 20, 'W');
	r.output(m);

}
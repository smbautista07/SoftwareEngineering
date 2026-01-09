#include <iostream>
#include <windows.h>

#include <iomanip>
#include <stdlib.h>
using namespace std;
#define map_width  20
#define map_height 30

const COLORREF rgbRed = 0x000000FF;
const COLORREF rgbGreen = 0x0000FF00;

struct entity_count_datatype
{
	short Zombie_count;
	int medkit_count;
	int food_count;
	int bullet_count;
	int wall_count;
} entity_count;

struct coord_pair
{
	short x;
	short y;
};

struct translation_pair //Almost the same as coordinates, but only used for movement. Makes code more digestable and readable
{
	short x_delta, y_delta;
};

struct map_change
{
	coord_pair coords;
	char map_symbol;
};

struct visual_change_pair 
{
	map_change m1, m2;
};

struct actual_coord_pair
{

};

//Function declaration

void initialise();
bool coin_flip()
{
	return rand() % 2;
}
bool coin_flip(float probability) //Overload for a bias coin
{
	return ((int)(probability*100) <= rand() % 100 + 1); //Without the extra 1 the range of values is 0 to 99
}
float percent_of_whole(int num1, int num2)
{
	return (float)num1 / (num1+num2);
}
int random_number()
{
	return rand();
}
int random_number(int max_value)
{
	return rand() % max_value + 1;
}
int random_number(int min_value, int max_value)
{
	return (rand() % max_value-min_value) + min_value + 1;
}
bool between_inclusive(int num1, int num2, int num3)
{
	int upper = max(num2, num3);
	int lower = min(num2, num3);
	return (num1 >= lower and num1 <= upper);
}
int how_many_are_true(bool condition_1 = false, bool condition_2 = false, bool condition_3 = false, bool condition_4 = false)
{
	return condition_1 + condition_2 + condition_3 + condition_4;
}
coord_pair translation(coord_pair &original_position, translation_pair change_in_position)
{
	coord_pair new_position = { original_position.x+change_in_position.x_delta, original_position.y+change_in_position.y_delta };
	return new_position;
}


class Map_decl
{
public:
	virtual bool within_grid(coord_pair c)
	{
		return false;
	}
	virtual bool set_map_char(map_change change_info, bool is_overriding = true, char allowed_character = '.')
	{
		return false;
	}
};

class Player
{
private:
	map_change map_info;
	int food, health, ammo, timer;
public:
	/*translation_pair input_to_movement()*/
	visual_change_pair input_to_movement(Map_decl &m)
	{
		translation_pair movement_value = { 0,0 };

		if (GetAsyncKeyState('W'))
		{
			movement_value.y_delta += -1;
		}

		if (GetAsyncKeyState('A'))
		{
			movement_value.x_delta += -1;
		}

		if (GetAsyncKeyState('S'))
		{
			movement_value.y_delta += 1;
		}

		if (GetAsyncKeyState('D'))
		{
			movement_value.x_delta += 1;
		}

		return move_on_map(movement_value, m);

		//return movement_value;
	}

	visual_change_pair move_on_map(translation_pair change_in_position, Map_decl &m)
	{
		coord_pair next_player_coords;
		visual_change_pair v = {};
		bool valid_movement = true;

		coord_pair x_move = { (short)(map_info.coords.x + change_in_position.x_delta), map_info.coords.y };
		coord_pair y_move = { map_info.coords.x, (short)(map_info.coords.y + change_in_position.y_delta) };

		//Invalidate the movement in the x or y direction 
		bool x_move_valid = m.within_grid(x_move) and change_in_position.x_delta != 0;
		bool y_move_valid = m.within_grid(y_move) and change_in_position.y_delta != 0;;

		int total_move_directions = x_move_valid + y_move_valid;
		switch (total_move_directions)
		{
		case 0:
			//if there's no movement, invalidate the movement
			valid_movement = false;
			break;
		case 1:
			//if there's only one, it must be one or the other. Find out what it is and adjust the new_player_coords accordingly.
			next_player_coords = (x_move_valid) ? x_move : y_move;
			break;
		case 2:
			next_player_coords = { x_move.x, y_move.y };
			break;
		}

		if (valid_movement)
		{
			//Place a '.' where the player just left
			map_change fill_exited_tile_change = { map_info.coords, '.' };
			m.set_map_char(fill_exited_tile_change);
			map_info.coords = next_player_coords;
			m.set_map_char(map_info);
			v = { fill_exited_tile_change, map_info };
		}
		//v is has data or is completely empty if the movement is invalid.
		return v;
	}

	//bool validate_one_dimension_movement(coord_pair c, int delta, Map_Handler m)
	//{
	//	return m.within_grid(c) and delta != 0;
	//}

	void set_map_info(map_change m)
	{
		map_info = m;
	}
	map_change get_map_info()
	{
		return map_info;
	}


};

class Map_Handler: public Map_decl
{
private:
	char map_info[map_height][map_width];
	map_change player_map_change_info = {coord_pair{NULL,NULL}, 'P'};
	map_change exit_map_change_info = {coord_pair{NULL,NULL}, 'E' };
public:
	Map_Handler()
	{
	}
	void generate_map(entity_count_datatype entity_count, Player &p) //Fill all the empty tiles with '.'
	{
		for (short i = 0; i < map_width; i++)
		{
			for (short j = 0; j < map_height; j++)
			{
				coord_pair current_coords = { i,j };
				map_change change_info = {current_coords, '.' };
				set_map_char(change_info);
			}
		}

		player_map_change_info.coords = random_coords();
		map_change temp = { random_coords(), 'P'};
		p.set_map_info(temp);


		exit_map_change_info.coords = random_coords();
		/*int player_x = 0;
		int player_y = 0;
		int exit_x = map_width - 1;
		int exit_y = map_height - 1;*/
		set_map_char(p.get_map_info());
		set_map_char(exit_map_change_info);
		make_playable_area(p);

		random_placements('Z', entity_count.Zombie_count);
		random_placements('+', entity_count.medkit_count, 'R');
		random_placements('F', entity_count.food_count, 'R');
		random_placements('B', entity_count.bullet_count), 'R';
		random_placements('#', entity_count.wall_count);
	}

	void make_playable_area(Player p)
	{
		int map_scaling_1 = map_width / 10;
		int map_scaling_2 = map_height / 10;
		for (int i = 0; i < map_scaling_1; i++)
		{
			create_turning_path_between(p.get_map_info().coords, exit_map_change_info.coords, random_number(map_scaling_1 - i, map_scaling_1), random_number(map_scaling_2 - i, map_scaling_2));
		}
		/*
		create_turning_path_between(player_x, player_y, exit_x, exit_y, 4, 3);
		create_turning_path_between(player_x, player_y, exit_x, exit_y, 3, 2);
		create_turning_path_between(player_x, player_y, exit_x, exit_y, 3, 3);*/
	}

	void random_placements(char c, int total_count, char allowed_character = '.')
	{
		for (int i = 0; i < total_count;)
		{
			//Keep rerolling until the stored character is one they're allowed to replace
			do
			{
			} while (!set_map_char(map_change{random_coords(), c}, false, allowed_character)); //Repeat until valid placement returned
			//Only increment 'i' after the value has been added
			i++;
		}
	}

	visual_change_pair move_player(translation_pair change_in_position)
	{
		coord_pair next_player_coords;
		visual_change_pair v = {};
		bool valid_movement = true;

		coord_pair x_move = {(short)(player_map_change_info.coords.x + change_in_position.x_delta), player_map_change_info.coords.y };
		coord_pair y_move = {player_map_change_info.coords.x, (short)(player_map_change_info.coords.y + change_in_position.y_delta) };
		
		
		//Invalidate the movement in the x or y direction 
		bool x_move_valid = within_grid(x_move) and change_in_position.x_delta != 0;
		bool y_move_valid = within_grid(y_move) and change_in_position.y_delta != 0;;

		int total_move_directions = x_move_valid + y_move_valid;
		switch (total_move_directions) 
		{
		case 0:
			//if there's no movement, invalidate the movement
			valid_movement = false;
			break;
		case 1:
			//if there's only one, it must be one or the other. Find out what it is and adjust the new_player_coords accordingly.
			next_player_coords = (x_move_valid) ? x_move : y_move;
			break;
		case 2:
			next_player_coords = { x_move.x, y_move.y };
			break;
		}

		if (valid_movement)
		{
			//Place a '.' where the player just left
			map_change fill_exited_tile_change = { player_map_change_info.coords, '.' };
			set_map_char(fill_exited_tile_change);
			player_map_change_info.coords = next_player_coords;
			set_map_char(player_map_change_info);
			v = { fill_exited_tile_change, player_map_change_info };
		}
		//v is has data or is completely empty if the movement is invalid.
		return v;
	}

	coord_pair random_coords()
	{
		coord_pair c = { rand() % map_width ,rand() % map_height };
		return c;
	}

	int random_x_coord()
	{
		return rand() % map_width;
	}

	int random_y_coord()
	{
		return rand() % map_height;
	}

	void create_turning_path_between(coord_pair coord_1, coord_pair coord_2, int path_width = 1, int extra_stops = 1)
	{
		coord_pair current_coords = coord_1;
		for (int i = 0; i < extra_stops; i++)
		{
			coord_pair new_coords = random_coords();
			create_path_between(current_coords, new_coords, path_width);
			current_coords = new_coords;
		}
		create_path_between(current_coords, coord_2, path_width);
	}

	void create_path_between(coord_pair coord_1, coord_pair coord_2, int path_width = 1)
	{
		//Create path from point 1 to point 2
		int x_current = coord_1.x;
		int y_current = coord_1.y;
		int x_end = coord_2.x;
		int y_end = coord_2.y;
		int x_increment = (x_current < x_end) ? 1 : -1;
		int y_increment = (y_current < y_end) ? 1 : -1;

		bool x_misaligned;
		bool y_misaligned;
		//if (x_misaligned and y_misaligned) //Prevent overwrite of starting tile
		//{
		//	//If neither are aligned, choose one or the other
		//	coin_flip() ? x_current += x_increment : y_current += y_increment;
		//}
		////Otherwise, choose the one that isn't aligned
		//else if (x_misaligned)
		//{
		//	x_current += x_increment;
		//}
		//else
		//{
		//	y_current += y_increment;
		//}
		//while (x_current != x_end or y_current != y_end)
		//{
		//	if (x_current != x_end and y_current != y_end) //If neither are equal
		//	{
		//		if (coin_flip())
		//		{
		//			set_map_char(x_current, y_current, 'R');
		//			x_current += x_increment;
		//		}
		//		else
		//		{
		//			set_map_char(x_current, y_current, 'R');
		//			y_current += y_increment;
		//		}
		//	}
		//	else if (x_current != x_end) //If only x is not aligned
		//	{
		//		set_map_char(x_current, y_current, 'R');
		//		x_current += x_increment;
		//	}
		//	else //If only y is not aligned
		//	{
		//		set_map_char(x_current, y_current, 'R');
		//		y_current += y_increment;
		//	}
		//}
		while (int true_condition_count = how_many_are_true(x_misaligned = (x_current != x_end), y_misaligned = (y_current != y_end)))
		{
			//Don't place anything if on the starting tile
			map_change change_info = { coord_pair{(short)(x_current), (short)(y_current)}, 'R'};
			set_rectangle_char(change_info, false, path_width, path_width);

			switch (true_condition_count)
			{
			case 2: //If neither x or y is aligned
				coin_flip(percent_of_whole(abs(y_end - y_current), abs(x_end - x_current))) ? x_current += x_increment : y_current += y_increment;
				break;
			case 1:
				//If x is not aligned, y needs to be incremented. If it is, the y needs to be incremented
				x_misaligned ? x_current += x_increment : y_current += y_increment; 
				break;
			}
		}
	}

	bool within_grid(coord_pair coords)
	{
		return between_inclusive(coords.x, 0, map_width - 1) and between_inclusive(coords.y, 0, map_height - 1);
	}

	void set_rectangle_char(map_change starting_change_info,bool is_overriding = true,short width = 1, short length = 1)
	{
		for (short i = 0; i < width; i++)
		{
			for (short j = 0; j < width; j++)
			{
				coord_pair current_coords = { (short)(starting_change_info.coords.x + i), (short)(starting_change_info.coords.y + j) };
				map_change new_change_info = { current_coords, starting_change_info.map_symbol };
				set_map_char(new_change_info, is_overriding);
			}
		}
			
	}

	bool set_map_char(map_change change_info, bool is_overriding = true, char allowed_character = '.')
	{
		bool valid_placement = true;
		if (within_grid(change_info.coords) == false) {valid_placement = false;}
		if (is_overriding == false and get_map_char(change_info.coords) != allowed_character) { valid_placement = false; }
		if (valid_placement) { map_info[change_info.coords.y][change_info.coords.x] = change_info.map_symbol;}
		return valid_placement; //Return value informs other functions on whether the placement was successful.
	}
	
	char get_map_char(coord_pair coords)
	{
		return map_info[coords.y][coords.x];
	}

};
//
//class Entity
//{
//protected:
//	char map_symbol;
//	short x_coord;
//	short y_coord;
//	short x_previous_visual;
//	short y_previous_visual;
//	bool movement_visual_change = false;
//public:
//	Entity(short x_in, short y_in, char map_symbol_in)
//	{
//		x_coord = x_in;
//		y_coord = y_in;
//		x_previous_visual = x_in;
//		y_previous_visual = y_in;
//		map_symbol = map_symbol_in;
//	}
//	void set_coords(short x_in, short y_in)
//	{
//		//Updates the previous position only once that was output by the renderer for erasure of its icon.
//		/*if (movement_visual_change == true)
//		{
//			x_previous_visual = x_coord;
//			y_previous_visual = y_coord;
//			movement_visual_change = false;
//		}*/
//		x_previous_visual = x_coord;
//		y_previous_visual = y_coord;
//		x_coord = x_in;
//		y_coord = y_in;
//	}
//
//	void move(short x_mov, short y_mov, Map_Handler m)
//	{
//		int x_new = x_coord + x_mov;
//		int y_new = y_coord + y_mov;
//
//		bool within_x_bounds = (0 <= x_new and x_new < map_width);
//		bool within_y_bounds = (0 <= y_new and y_new < map_height);
//
//		bool is_wall = m.get_map_char(x_new, y_new) == 'W';
//
//		bool x_valid = (within_x_bounds and !is_wall);
//		bool y_valid = (within_y_bounds and !is_wall);
//
//		//Ternary operators to check whether the entity is going to move out of bounds
//		x_mov = x_valid ? x_mov : 0;
//		y_mov = y_valid ? y_mov : 0;
//
//		set_coords(x_coord + x_mov, y_coord + y_mov);
//	}
//
//
//	
//	void set_movement_visual_change(bool b)
//	{
//		movement_visual_change = b;
//	}
//
//	short get_x_coord()
//	{
//		return x_coord;
//	}
//
//	short get_y_coord()
//	{
//		return y_coord;
//	}
//
//	short get_x_prev_visual_coord()
//	{
//		return x_previous_visual;
//	}
//
//	short get_y_prev_visual_coord()
//	{
//		return y_previous_visual;
//	}
//
//	bool get_movement_visual_change()
//	{
//		return movement_visual_change;
//	}
//
//	char get_map_symbol()
//	{
//		return map_symbol;
//	}
//};

//class Player : public Entity
//{
//private:
//	bool last_moved_horizontal = false;
//public:
//	Player(short x_in, short y_in) : Entity(x_in, y_in, 'P')
//	{
//	}
//	void input_to_movement(Map_Handler m)
//	{
//		int x_move = 0;
//		int y_move = 0;
//
//		if (GetAsyncKeyState('W'))
//		{
//			y_move += -1;
//		}
//
//		if (GetAsyncKeyState('A'))
//		{
//			x_move += -1;
//		}
//
//		if (GetAsyncKeyState('S'))
//		{
//			y_move += 1;
//		}
//
//		if (GetAsyncKeyState('D'))
//		{
//			x_move += 1;
//		}
//
//		move(x_move, y_move, m);
//
//	}
//	void move(short x_mov, short y_mov, Map_Handler m)
//	{
//		if (x_mov and y_mov) //If the player wants to move both horizontally and vertically:
//			//alternate between the two.
//		{
//			if (last_moved_horizontal)
//			{
//				Entity::move(0, y_mov, m);
//				last_moved_horizontal = false;
//			}
//			else
//			{
//				Entity::move(x_mov, 0, m);
//				{
//					last_moved_horizontal = true;
//				}
//			}
//		}
//		else if(x_mov or y_mov) //If one of the buttons are pressed
//		{
//			Entity::move(x_mov, y_mov, m);
//			last_moved_horizontal = x_mov; //Only one or the other can have a value now, so the value of one indicates the other.
//		}
//	}
//};

class Renderer
{
private:
	HANDLE Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	short map_element_spacing = 2;
	COORD origin = { (short)0,(short)0 };
public:
	Renderer()
	{

	}
	
	void initialise() //Hide cursor
	{
		CONSOLE_CURSOR_INFO c;
		c.dwSize = 100;
		c.bVisible = false;
		SetConsoleCursorInfo(Screen, &c);
	}

	void visual_update(visual_change_pair updated_visual_information, Map_Handler m)
	{
		//If both characters are the same there's no point in doing a visual update.
		if (updated_visual_information.m1.map_symbol != updated_visual_information.m2.map_symbol)
		{
			COORD position1 = { updated_visual_information.m1.coords.x * map_element_spacing,updated_visual_information.m1.coords.y };
			COORD position2 = { updated_visual_information.m2.coords.x * map_element_spacing,updated_visual_information.m2.coords.y };

			SetConsoleCursorPosition(Screen, position1);

			cout << m.get_map_char(updated_visual_information.m1.coords);
			SetConsoleCursorPosition(Screen, position2);
			cout << m.get_map_char(updated_visual_information.m2.coords);
		}
		
	}


	void output(Map_Handler m)
	{
		SetConsoleCursorPosition(Screen, origin);
		system("cls");

		for (short j = 0; j < map_height; j++) //For each row
		{
			for (short i = 0; i < map_width; i++) //For each column
			{
				coord_pair coords = { i,j };
				char c = m.get_map_char(coords);
				if (c == 'R')
				{
					cout << '.';
				}
				else
				{
					cout << c;
				}
				cout << setw(map_element_spacing); //Output the character stored
			}
			cout << "\n"; //Start a new line
		}


	}

	//void output(Entity &e)
	//{
	//	/*if (e.get_movement_visual_change() == false)
	//	{
	//		fill_char(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
	//		fill_char(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
	//		e.set_movement_visual_change(true);
	//	}*/
	//	fill_char(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
	//	fill_char(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
	//}

	void fill_char(short x_coord, short y_coord, char character)
		{
			COORD position = { (short)(x_coord * map_element_spacing), y_coord };
			SetConsoleCursorPosition(Screen, position); //Move cursor to a specific position on screen
			cout << character;
			SetConsoleCursorPosition(Screen, origin);
		}
};

//<< setw(map_element_spacing)
//			cout << "\n";


Renderer r;
Map_Handler m;
Player p;


//Player Player_Obj = Player(4, 4);
short map_element_spacing = 2;

int main()
{
	initialise();

	while (true)
	{
		Sleep(100);

		//translation_pair final_player_movement = p.input_to_movement();




		/*visual_change_pair player_movement_visual_update = m.move_player(final_player_movement);*/

		visual_change_pair player_movement_visual_update = p.input_to_movement(m);

		r.visual_update(player_movement_visual_update , m);


		//Player_Obj.input_to_movement(m);

		//r.output(Player_Obj);
	}

	return 0;
}

void initialise()
{
	srand((unsigned int)time(NULL));

	
	entity_count.Zombie_count = 1;
	entity_count.medkit_count = 10;
	entity_count.food_count = 10;
	entity_count.bullet_count = 10;
	entity_count.wall_count = 10;

	m.generate_map(entity_count, p);
	
	r.output(m);
}
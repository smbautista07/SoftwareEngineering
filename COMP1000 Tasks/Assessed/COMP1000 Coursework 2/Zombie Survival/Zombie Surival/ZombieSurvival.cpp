#include <iostream>
#include <windows.h>

#include <iomanip>
#include <stdlib.h>

using namespace std;
#define map_width  50
#define map_height 50

struct entity_count_datatype
{
	short Zombie_count;
	short medkit_count;
	short food_count;
	short bullet_count;
	short wall_count;
} entity_count;

struct resource
{
	string name;
	short value;
};

struct player_resources
{
	short food, health, ammo, timer, score;
}; 

struct coord
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
	coord coords;
	char map_symbol;
};

struct coord_pair 
{
	coord coord1, coord2;
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
	return (rand() % (max_value - min_value + 1) + min_value);
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
coord translation(coord original_position, translation_pair change_in_position)
{
	coord new_position = { original_position.x+change_in_position.x_delta, original_position.y+change_in_position.y_delta };
	return new_position;
}

//Declare map and the functions that will be used in Player class
class Map_decl
{
public:
	virtual bool within_grid(coord c)
	{
		return false;
	}
	virtual bool set_map_char(map_change change_info, bool is_overriding = true, char allowed_character = '.')
	{
		return false;
	}
	virtual char get_map_char(coord c)
	{
		return '.';
	}
};

class Player
{
private:
	map_change map_info;
	static const short resource_type_count = 5;
	short indexed_resource_values[resource_type_count];
	string indexed_resource_names[resource_type_count] = { "Food", "Health", "Ammo", "Time", "Score"};
	bool visually_up_to_date[resource_type_count]{ false,false,false,false,false };

public:
	/*translation_pair input_to_movement()*/
	coord_pair input_to_movement(Map_decl &m)
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

	

	coord_pair move_on_map(translation_pair change_in_position, Map_decl &m)
	{
		coord next_player_coords;
		coord_pair v = {};
		bool valid_movement = true;
		bool last_moved_x = true;

		coord x_move = { (short)(map_info.coords.x + change_in_position.x_delta), map_info.coords.y };
		coord y_move = { map_info.coords.x, (short)(map_info.coords.y + change_in_position.y_delta) };
		coord xy_move = { x_move.x, y_move.y };
		
		bool x_move_valid = m.within_grid(x_move) and change_in_position.x_delta != 0 and m.get_map_char(x_move) != 'Z' and m.get_map_char(x_move) != '#';
		bool y_move_valid = m.within_grid(y_move) and change_in_position.y_delta != 0 and m.get_map_char(y_move) != 'Z' and m.get_map_char(y_move) != '#';
		bool xy_move_valid = m.within_grid(xy_move) and change_in_position.y_delta != 0 and m.get_map_char(xy_move) != 'Z' and m.get_map_char(xy_move) != '#';
		//Invalidate the movement in the x or y direction 
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
			if (xy_move_valid)
			{
				next_player_coords = xy_move;
			}
			else
			{
				next_player_coords = coin_flip() ? x_move : y_move;
			}
			break;
		}

		if (valid_movement)
		{
			interact_with_tile(next_player_coords, m);
			//Place a '.' where the player just left
			map_change fill_exited_tile_change = { map_info.coords, '.' };
			m.set_map_char(fill_exited_tile_change);
			map_info.coords = next_player_coords;
			m.set_map_char(map_info);
			v = { fill_exited_tile_change.coords, map_info.coords};
		}

		post_move_zombie_interaction(map_info.coords, m);

		//v is has data or is completely empty if the movement is invalid.
		return v;
	}

	void post_move_zombie_interaction(coord current_tile, Map_decl& m)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				coord checked_tile = { current_tile.x + i, current_tile.y + j };
				if (m.get_map_char(checked_tile) == 'Z')
				{
					increment_resource("Health", -1);
				}
			}
		}
	}


	void interact_with_tile(coord new_tile, Map_decl &m)
	{
		char c = m.get_map_char(new_tile);
		switch (c)
		{
		case '+':
			increment_resource("Health", 1);
			break;
		case 'F':
			increment_resource("Score", 50);
			break;
		case 'B':
			increment_resource("Bullets", 1);
			break;
		}
		

	}

	void set_map_info(map_change m)
	{
		map_info = m;
	}
	map_change get_map_info()
	{
		return map_info;
	}

	void set_resources(player_resources initial_values)
	{
		indexed_resource_values[0] = initial_values.food;
		indexed_resource_values[1] = initial_values.health;
		indexed_resource_values[2] = initial_values.ammo;
		indexed_resource_values[3] = initial_values.timer;
		indexed_resource_values[4] = initial_values.score;
	}

	short get_resource_type_count()
	{
		return resource_type_count;
	}

	void increment_resource(string name, short value)
	{
		int i = find_resource_index(name);

		if (i >= 0)
		{
			indexed_resource_values[i] += value;
			set_visually_up_to_date(i, false);
		}
	}
	int find_resource_index(string name)
	{
		short i;
		for (i = 0; i < resource_type_count; i++)
		{
			if (name == indexed_resource_names[i])
			{
				return i;
			}
		}
		//If unsuccessful
		return i = -1;
	}
	void set_visually_up_to_date(short index, bool value)
	{
		visually_up_to_date[index] = value;
	}

	bool get_visually_up_to_date(short index)
	{
		return visually_up_to_date[index];
	}
	string get_resource_name(short index)
	{
		return indexed_resource_names[index];
	}
	short get_resource_value(short index)
	{
		return indexed_resource_values[index];
	}

	
};

class Map_Handler: public Map_decl
{
private:
	char map_info[map_height][map_width];
	//map_change player_map_change_info = {coord{NULL,NULL}, 'P'};
	map_change exit_map_change_info = {coord{NULL,NULL}, 'E' };

	coord visual_update_needed[500];
	short pointer = 0;
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
				coord current_coords = { i,j };
				map_change change_info = {current_coords, '.' };
				set_map_char(change_info);
			}
		}

		map_change temp = { random_coords(), 'P'};
		p.set_map_info(temp);


		exit_map_change_info.coords = random_coords();
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
	
	bool in_change_array(coord c)
	{
		for (int i = 0; i < 500; i++)
		{
			if (c.x == visual_update_needed[i].x)
			{
				if (c.y == visual_update_needed[i].y)
				{
					return true;
				}
			}
		}
		return false;
	}


	void move_zombies()
	{
		for (short i = 0; i < map_width; i++)
		{
			for (short j = 0; j < map_height; j++)
			{
				coord current_coord = { i,j };
				if (get_map_char(current_coord) == 'Z')
				{
					short x_change = random_number(-1, 1);
					short y_change = random_number(-1, 1);
					coord new_position = { i+x_change, j+y_change };
					if (within_grid(new_position) and in_change_array(new_position) == false and x_change != 0 and y_change != 0)
					{
						swap (current_coord, new_position);

					}
				}
			}
		}
	}
	bool pointer_nonzero()
	{
		return pointer;
	}
	
	void add_to_visual_updates(coord c)
	{
		if (pointer < 500)
		{
			visual_update_needed[pointer] = c;
			pointer += 1;
		}
	}

	coord remove_from_visual_updates()
	{
		if (pointer > 0)
		{
			pointer += -1;
			return visual_update_needed[pointer];
		}
	}

	void swap(coord position_1, coord position_2)
	{
		char char_1 = get_map_char(position_1);
		char char_2 = get_map_char(position_2);

		set_map_char(map_change{ position_1, char_2 });
		set_map_char(map_change{ position_2, char_1 });

		add_to_visual_updates(position_1);
		add_to_visual_updates(position_2);

	}



	coord random_coords()
	{
		coord c = { rand() % map_width ,rand() % map_height };
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

	void create_turning_path_between(coord coord_1, coord coord_2, int path_width = 1, int extra_stops = 1)
	{
		coord current_coords = coord_1;
		for (int i = 0; i < extra_stops; i++)
		{
			coord new_coords = random_coords();
			create_path_between(current_coords, new_coords, path_width);
			current_coords = new_coords;
		}
		create_path_between(current_coords, coord_2, path_width);
	}

	void create_path_between(coord coord_1, coord coord_2, int path_width = 1)
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
			map_change change_info = { coord{(short)(x_current), (short)(y_current)}, 'R'};
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

	bool within_grid(coord coords)
	{
		return between_inclusive(coords.x, 0, map_width - 1) and between_inclusive(coords.y, 0, map_height - 1);
	}

	void set_rectangle_char(map_change starting_change_info,bool is_overriding = true,short width = 1, short length = 1)
	{
		for (short i = 0; i < width; i++)
		{
			for (short j = 0; j < width; j++)
			{
				coord current_coords = { (short)(starting_change_info.coords.x + i), (short)(starting_change_info.coords.y + j) };
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
	
	char get_map_char(coord coords)
	{
		return map_info[coords.y][coords.x];
	}

};

class Renderer
{
private:
	HANDLE Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	short map_element_spacing = 2;
	COORD origin = { (short)0,(short)0 };
	CONSOLE_CURSOR_INFO cci;
public:
	Renderer()
	{

	}
	
	void hide_cursor() //Hide cursor
	{
		cci.dwSize = 100;
		cci.bVisible = false;
		SetConsoleCursorInfo(Screen, &cci);
	}

	void visual_update(coord_pair updated_visual_information, Map_Handler m)
	{

		//If both characters are the same there's no point in doing a visual update.
		char symbol1 = m.get_map_char(updated_visual_information.coord1);
		char symbol2 = m.get_map_char(updated_visual_information.coord2);

		if (symbol1 != symbol2)
		{
			write_at_spaced_location(updated_visual_information.coord1, symbol1);
			write_at_spaced_location(updated_visual_information.coord2, symbol2);

		}
		
	}


	void output_map(Map_Handler m)
	{
		SetConsoleCursorPosition(Screen, origin);
		system("cls");

		for (short j = 0; j < map_height; j++) //For each row
		{
			for (short i = 0; i < map_width; i++) //For each column
			{
				coord coords = { i,j };
				char c = m.get_map_char(coords);
				if (c == 'R')
				{
					cout << '.';
				}
				else
				{
					cout << c;
				}
				cout << setw(map_element_spacing); //output the character stored
			}
			cout << "\n"; //Start a new line
		}
	}


	void output_HUD(Player p)
	{
		int spacing = max(8,map_width / p.get_resource_type_count());

		for (int i = 0; i < p.get_resource_type_count(); i++)
		{
			if (p.get_visually_up_to_date(i) == false)
			{
				write_at_spaced_location(coord{ (short)(spacing * i), map_height + 1 }, p.get_resource_name(i), p.get_resource_value(i));
				p.set_visually_up_to_date(i, true);
			}
		}

	}

	void visual_update_zombies(Map_Handler &m)
	{
		while (m.pointer_nonzero())
		{
			coord c = m.remove_from_visual_updates();
			char ch = m.get_map_char(c);
			write_at_spaced_location(c, ch);
		}
	}

	//void output(Entity &e)
	//{
	//	/*if (e.get_movement_visual_change() == false)
	//	{
	//		write_at_location(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
	//		write_at_location(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
	//		e.set_movement_visual_change(true);
	//	}*/
	//	write_at_location(e.get_x_prev_visual_coord(), e.get_y_prev_visual_coord(), '.');
	//	write_at_location(e.get_x_coord(), e.get_y_coord(), e.get_map_symbol());
	//}

	void move_cursor_to_spaced_location(coord c)
	{
		COORD C = { (short)(c.x * map_element_spacing), c.y };
		SetConsoleCursorPosition(Screen, C); //Move cursor to a specific position on screen
	}
	void write_at_spaced_location(coord c, char character)
	{
		move_cursor_to_spaced_location(c);
		if (character == 'R')
		{
			cout << '.';
		}
		else
		{
			cout << character;
		}
		
		
	}
	void write_at_spaced_location(coord c, string message)
	{
		
		move_cursor_to_spaced_location(c);
		cout << message;
	}
	void write_at_spaced_location(coord c, string resource_name, int resource_value)
	{
		move_cursor_to_spaced_location(c);
		cout << resource_name << ": " << resource_value;
	}
};


Renderer r;
Map_Handler m;
Player p;


short map_element_spacing = 2;

int main()
{
	initialise();

	int cooldown = 15;
	int cycles = 0;


	while (p.get_resource_value(1) > 0 )
	{
		Sleep(100);

		coord_pair map_change_locations = p.input_to_movement(m);

		r.visual_update(map_change_locations , m);
		r.output_HUD(p);

		p.increment_resource("Time", -1);

		m.move_zombies();

		r.visual_update_zombies(m);

		if (cycles >= cooldown)
		{
			r.hide_cursor();

		}
		cycles += 1;
	}

	return 0;
}

void initialise()
{
	srand((unsigned int)time(NULL));

	r.hide_cursor();

	entity_count.Zombie_count = 20;
	entity_count.medkit_count = 40;
	entity_count.food_count = 40;
	entity_count.bullet_count = 40;
	entity_count.wall_count = 80;

	player_resources ree;

	ree.food =100;
	ree.health = 5;
	ree.ammo = 0;
	ree.timer =  300 ;
	ree.score = 0 ;
	


	p.set_resources(ree);

	m.generate_map(entity_count, p);
	
	r.output_map(m);
}
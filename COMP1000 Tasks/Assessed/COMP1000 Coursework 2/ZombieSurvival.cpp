#include <iostream>
#include <iomanip>

#define width 50
#define height 50
char map[width][height];

void render_map()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height;j++)
		{
			std::cout << std::setw(2)<< map[i][j];
		}
		std::cout << "\n";
	}
}

int main()
{
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height;j++)
		{
			map[i][j] = '.';
		}
	}

	map[5][2] = 'A';
	map[4][2] = 'O';
	
	render_map();
		


	return 0;
}


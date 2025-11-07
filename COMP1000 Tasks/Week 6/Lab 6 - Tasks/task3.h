#include "shared_task_library.h"

void file_read_chars(string file_name)
{
	ifstream fr;
	char output_char;

	int line_count = count_lines(file_name);


	fr.open(file_name);
	if (fr.is_open())
	{
		while (fr.get(output_char))
		{
			cout << output_char << "\n";
		}
		fr.close();
	}
	else
	{
		file_error_message(file_name, "read");
	}
}

void task3()
{
	file_reset("move_to.txt");
	file_read_chars("test.txt");
	
}
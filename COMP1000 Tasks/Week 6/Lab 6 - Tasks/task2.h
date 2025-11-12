#include "shared_task_library.h"


void task2()
{
	file_reset("task2.txt");
	file_append_line("task2.txt", "4534343");
	file_append_line("task2.txt", "4983439");
	file_read_lines("task2.txt");
}
#include <stdio.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"

using namespace std;

double sum;

int main()
{
	for (int x = 10; x < 210; x+=10 )
	{
		sum = 0;
		for (int i = 0; i < x; i += 10)
		{
			sum += task1Amended();
		}
		printf("%f\n",sum / 10);
	}

	return 0;
}
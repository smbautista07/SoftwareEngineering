#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

void task4()
{
	vector<int> int_values;
	int_values.push_back(32);
	int_values.push_back(33);
	int_values.push_back(34);
	for (int i = 0; i < int_values.size(); i++)
	{
		cout << int_values[i];
	}
	cout << "\n";


	stack<char> stack_example;
	for (int i = 0; i < 26; i++)
	{
		stack_example.push((char)('a' + i));
	}

	for (int i = stack_example.size(); i > 0; i--)
	{
		cout << stack_example.top();
		stack_example.pop();
	}
	cout << "\n";

	map<char, string> map_example;

	map_example.emplace('a', "apple" );
	map_example.emplace('a', "Apple" );
	cout << map_example['a'];

}
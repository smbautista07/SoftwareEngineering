//Installs libraries which are responsible for inputs, outputs etc
#include <iostream>
//Ensures a namespace does not neet to be written every time when interacting 
//with declared variables
using namespace std;

void task1() //Practice with variables
{
    string name;
    int age;
    float height;
    char grade;

    name = "Alice";
    age = 20;
    height = 1.65;
    //Characters specifically have single quotes in C++
    // unlike python which has no distinction between them.
    grade = 'B'; 
    //"cout" stands for character out, displays 
    //the value handled by the insertion operator << 
    cout << name << "\n" << age << "\n" << height << "\n" << grade<< "\n";
    
    name = "Bob";
    age = 22;
    height = 1.75;
    grade = 'A'; 
    cout << name << "\n" << age << "\n" << height << "\n" << grade<< "\n";    
}

void task2()
{
    int num1;
    int num2;
    num1 = 12;
    num2 = 5;
    cout << num1+num2 << "\n";
    cout << num1-num2 << "\n";
    cout << num1/num2 << "\n"; // Integer values lose any decimal part of the number so 0.66 becomes 0
    cout << num1/float(num2) << "\n"; // rank promotion 
    cout << num1*num2 << "\n";
    cout << num1%num2 << "\n";


}

void task3()
{
    //local1
    int x = 1;
    cout << x;
    void myfunction()
    {
        cout<< x;
        //local2
        int x = 2;
        cout  << x;
    }

}
int main()
{
    //task1();
    task2();
    return 0;
}


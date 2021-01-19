#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int sum(int x, int y)
{
	int sum;
	sum = x + y;
	return sum;
}

void sum(int a1, int a2, int b1, int b2)
{
	int sum1, sum2;
	
	sum1 = a1 + b1;
	sum2 = a2 + b2;
	if (sum2 > 0)
	{
		cout << sum1<<"+"<<sum2<<"i";
	}
	
	else
	{
		cout << sum1<<sum2<<"i";
	}
	
	
	
	
}

int main(int argc, char** argv) {
	
	setlocale(LC_ALL,"Russian");
    setlocale(LC_ALL,"rus");
    int a,b,a1,a2,b1,b2;
    int c;
    cout<<"a+b \n";
    cout<<"a = ";
    cin>>a;
    cout<<"b = ";
    cin>>b;
	int s1 = sum(a,b);
	
	cout<<"a+b= "<<s1<<"\n";
	
	cout<<"z1 = a1+b1 i, z2 = a2+b2 i \n";
    cout<<"a1 = ";
    cin>>a1;
    cout<<"b1 = ";
    cin>>b1;
    cout<<"a2 = ";
    cin>>a2;
    cout<<"b2 = ";
    cin>>b2;
	cout<<"z1 + z2 = ";
	sum(a1,b1,a2,b2);
	cin>>c;
	return 0;
}

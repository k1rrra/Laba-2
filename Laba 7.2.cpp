#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int sum (int k, ...)

{
int *p = &k; 
int s=0;

for ( ; k!=0;k--) s+= *p;

return s;
}

int main()
{

cout<<"\n(1,2,3)= "<<sum(3, 1,2,3); 
cout<<"\n(1,2,3,4,5,6,7)= "<<sum(7, 1,2,3,4,5,6,7); 
cout<<"\n(1,2,3,4,5,6,7,8,9,10,11)= "<<sum(11, 1,2,3,4,5,6,7,8,9,10,11)<<"\n"; 

system("pause");
return 1;
}

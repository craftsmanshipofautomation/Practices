#include "aeparser.hpp"
#include <iostream>


using namespace std;

int main()
{
   cout << AEParser("(1+1)").Parse() << endl;
   cout << AEParser("((1+1)+3)").Parse() << endl;
   cout << AEParser("((1+1)+(2+3))").Parse() << endl;
   cout << AEParser("(1+sin(0))").Parse() << endl;
   cout << AEParser("((1+sin(0)) * (3.0 + 4*5))").Parse() << endl;
}
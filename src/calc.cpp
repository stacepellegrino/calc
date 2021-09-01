#include <iostream>
#include <strstream>

#include "syntax.h"

using namespace std;

extern int getexpr();

int main ()
{
    cout << "Mixed-base expression executes after EOF\n";
    try {
        cout << getexpr();
    }
    catch (SyntaxError& s)
    {
        cout << "Error: " << s.message() << "\n";
    }
    return 0;
}


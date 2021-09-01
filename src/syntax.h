#ifndef __SYNTAX_H
#define __SYNTAX_H

#include <string>

using namespace std;

class SyntaxError
{
  public:
    SyntaxError(string s, int l, int c) : msg(s)    { lin = l; col = c; }
    string  message()                               { return msg; }
    int     line()                                  { return lin; }
    int     column()                                { return col; }
  private:
    string  msg;
    int     lin;
    int     col;
};

#endif

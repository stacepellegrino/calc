#ifndef _LEXBASE_H
#define _LEXBASE_H

#include <iostream>
#include <string>
#include <map>
#include <ctype.h>

using namespace std;

class Token {
  public:
    virtual void dump()         { cout << "??"; }
};

class Lex {
  public:

    Lex             (istream& s, bool c = true);
    virtual ~Lex    ();
    Token*          next();
    int             line()      { return tline; }
    int             column()    { return tcolumn; }

  protected:

    virtual Token*  scan();
    virtual bool    ignore()    { return isspace(curr); }
    virtual bool    comment()   { return false; }
    char            getchar();
    char            peekchar()  { return stream->peek(); }

    typedef map<string,Token*>  tokenmap;

    char        curr;
    tokenmap    reserved;

  private:

    int         lineno;
    int         columnno;
    int         tline;
    int         tcolumn;
    bool        keepcase;
    bool        eol;
    istream*    stream;
};

class Identifier : public Token {
  public:
    Identifier (string s)       { n = s; }
    string name()               { return n; }
    virtual void dump()         { cout << "IDENT(" << n << ")"; }
  private:
    string n;
};

class Number : public Token {
  public:
    Number (int n)              { v = n; }
    int value()                 { return v; }
    virtual void dump()         { cout << "NUMBER(" << v << ")"; }
  private:
    int v;
};

class ErrorToken : public Token {
  public:
    ErrorToken (char c)         { v = c; }
    char value ()               { return v; }
    virtual void dump()         { cout << "ERROR(" << v << ")"; }
  private:
    char v;
};

#endif

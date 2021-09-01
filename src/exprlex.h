#ifndef _EXPRLEX_H
#define _EXPRLEX_H

#include "lexbase.h"

class ExprLex : public Lex {
  public:
    ExprLex         (istream& s)
                    : Lex(s,false)    { }
  protected:
    virtual Token*  scan();
};

class Left       : public Token { };
class Right      : public Token { };

class Operator   : public Token {
  public:
    virtual int apply (int l, int r) = 0;
};

class AddOp      : public Operator { };
class Add        : public AddOp {
  public:
    virtual int apply (int l, int r)
      { return l + r; }
};
class Sub        : public AddOp {
  public:
    virtual int apply (int l, int r)
      { return l - r; }
};

class MulOp      : public Operator { };
class Mul        : public MulOp {
  public:
    virtual int apply (int l, int r)
      { return l * r; }
};
class Div        : public MulOp {
  public:
    virtual int apply (int l, int r)
      { return l / r; }
};

class PowOp      : public Operator { };
class Pow        : public PowOp {
  public:
    virtual int apply (int l, int r)
      { 
      	int result = l;
      	for (int i = 1; i < r; i++) 
      		result *= l; 
      	return result;
      }
};

#endif

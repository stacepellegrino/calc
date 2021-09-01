#include "exprlex.h"

Token* ExprLex::scan()
{
    if (curr == '(') {
        getchar();
        return new Left;
    }
    else if (curr == ')') {
        getchar();
        return new Right;
    }
    else if (curr == '+') {
        getchar();
        return new Add;
    }
    else if (curr == '-') {
        getchar();
        return new Sub;
    }
    else if (curr == '*') {
        getchar();
        return new Mul;
    }
    else if (curr == '/') {
        getchar();
        return new Div;
    }

    else if (curr == '^') {
        getchar();
        return new Pow;
    }

    else {
        return Lex::scan();
    }
}


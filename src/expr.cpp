#include <strstream>

#include "exprlex.h"
#include "syntax.h"

Token* token;

int expr(ExprLex& lex);
int term(ExprLex& lex);
int factor(ExprLex& lex);
int power(ExprLex& lex);

int getexpr()
{
    ExprLex e(cin);
    token = e.next();
    return expr(e);
}

int expr(ExprLex& lex)
{
    int left = term(lex);
    while (AddOp* op = dynamic_cast<AddOp*>(token)) {
        token = lex.next();
        int right = term(lex);
        left = op->apply(left,right);
    }
    return left;
}

int term(ExprLex& lex)
{
    int left = power(lex);
    while (MulOp* op = dynamic_cast<MulOp*>(token)) {
        token = lex.next();
        int right = power(lex);
        left = op->apply(left,right);
    }
    return left;
}


int factor(ExprLex& lex)
{
    if (Number* n = dynamic_cast<Number*>(token)) {
        token = lex.next();
        return n->value();
    }
    else if (dynamic_cast<Left*>(token)) {
        token = lex.next();
        int result = expr(lex);
        if (dynamic_cast<Right*>(token)) {
            token = lex.next();
            return result;
        }
        else if (dynamic_cast<ErrorToken*>(token)) {
            throw SyntaxError("Invalid character",
                              lex.line(), lex.column());
        }
        else {
            throw SyntaxError("Right parenthesis expected",
                              lex.line(), lex.column());
        }
    }
    else if (dynamic_cast<ErrorToken*>(token)) {
        throw SyntaxError("Invalid character",
                          lex.line(), lex.column());
    }
    else {
        throw SyntaxError("Operand expected",
                          lex.line(), lex.column());
    }
}

int power(ExprLex& lex)
{
    int left = factor(lex);
    while (PowOp* op = dynamic_cast<PowOp*>(token)) {
        token = lex.next();
        int right = factor(lex);
        left = op->apply(left,right);
    }
    return left;
}


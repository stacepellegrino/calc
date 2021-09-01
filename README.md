# calc
Mixed-base expression parser allowing for calculations between hexadecimal (base 16), denary (base 10),  octal  (base  8)  and  binary (base 2).

## Building
To compile the code execute:
```
$ g++ -o calc calc.cpp expr.cpp exprlex.cpp lexbase.cpp
```

To read the manpage execute:
```
$ man ./calc.1
```

## Description
**calc** is a parser for arithmetic operations such as, addition, subtraction, multiplication, division and powers, using any  supported  mixed-base values, which can be expressed as a combination of different bases in the same expression. Parenthesis are also supported for expressions, also enforcing precedence.

NOTE:  The  answer  written to STDOUT is always denary (base 10) and at present is only an integer, whereby decimal values get rounded down  to the nearest integer.

For  defining the base of a number in an expression requires one of the following prefixes:

       Hexadecimal (base 16): $[number]
       Octal (base 8)       : ![number]
       Binary (base 2)      : &[number]
       Power                : [number]^[number]

NOTE: Denary (base 10) has no prefix.

## Running
Two different examples are:
```
$ ./calc
Mixed-base expression executes after EOF
$F * &101 - (2^3)
EOF
67
```
```
$ ./calc
Mixed-base expression executes after EOF
((!130 - &1000) * $A) / 2
EOF
400
```

#include <map>

#include "lexbase.h"

using namespace std;

Lex::Lex(istream& s, bool c)
{
	curr = ' ';
	stream = &s;
	lineno = 1;
	tline = 1;
	columnno = 0;
	tcolumn = 0;
	keepcase = c;
    	eol = false;
}

Lex::~Lex()
{
	tokenmap::iterator i;
	for (i = reserved.begin(); i != reserved.end(); i++) 
	{
       		delete (*i).second;
	}
}

char Lex::getchar()
{
	if (stream->eof()) 
	{
     		curr = EOF;
    	}
    	else 
	{
        	stream->get(curr);
	        columnno++;
        	if (eol) 
		{
            		lineno++;
			columnno = 1;
        	}
        	eol = (curr == '\n');
	}
	return curr;
}

Token* Lex::next()
{
	for (;;) 
	{
        	while (curr != EOF && ignore()) 
		{
            		getchar();
        	}
        	if (!comment()) 
		{
            	break;
        	}
    	}
    	if (curr == EOF) 
	{
        	return 0;
    	}
    	else 
	{
        	tline = lineno;
	        tcolumn = columnno;
        	return scan();
    	}
}

Token* Lex::scan()
{
	if (isalpha(curr)) 
	{
        	string s;
        	while (isalpha(curr) || isdigit(curr)) 
		{
            		if (!keepcase) 
			{
                		curr = tolower(curr);
            		}
            		s += curr;
            		getchar();
        	}

	        tokenmap::iterator i = reserved.find(s);
	        if (i != reserved.end()) 
		{
        		return (*i).second;
	        }
        	else 
		{
        		return new Identifier(s);
        	}
    	}
    	else if (isdigit(curr) || (curr == '-' && isdigit(stream->peek()))) 
	{
        	bool s = (curr == '-');			
        	if (s) 
		{
            		getchar();
        	}

        	int n = 0;
        	while (isdigit(curr)) 
		{
            		n = n * 10 + curr - '0';
            		getchar();
        	}
        	if (s) 
		{
            		n = -n;
		}
        	return new Number(n);
	}
	else if (curr == '&' && (isdigit(stream->peek())) || stream->peek() == '-')
	{
	        getchar();

        	bool s = (curr == '-');				
        	if (s) 						 
		{
            		getchar();
        	}
		int n = 0;

		while (isdigit(curr))
		{
			n = n * 2 + curr - '0';
			getchar();
		}
        	if (s) 
		{
	       		n = -n;
		}		
		return new Number(n);
	}

	else if (curr == '!' && (isdigit(stream->peek())) || stream->peek() == '-') 
	{
	        getchar();

        	bool s = (curr == '-');
        	if (s)
		{
            		getchar();
        	}
		int n = 0;

		while (isdigit(curr))		// && curr <= 7) 
		{
			n = n * 8 + curr - '0';
			getchar();
		}
        	if (s) 
		{
	        	n = -n;
		}		
		return new Number(n);
	}

	else if (curr == '$' && (isxdigit(stream->peek())) || stream->peek() == '-')
	{
	        getchar();

        	bool s = (curr == '-');	
        	if (s)
		{
            		getchar();
        	}

        	int x = 0; 
		int n = 0;

		while (isxdigit(curr))
		{
			if (isdigit(curr)) 
			{
        			x = curr - 48; 		// Where 48 is the ASCII value for '0'.
	        	}
			else if (isalpha(curr)) 
			{
				if (islower(curr))
				{
					curr = toupper(curr);
				}
				x = curr - 55;
			}
			n = n * 16 + x;
			getchar();
		}
        	if (s) 
		{
            		n = -n;
		}		
		return new Number(n);
	}

	else 
	{
        	Token* t = new ErrorToken(curr);
	        getchar();
        	return t;
    	}
}

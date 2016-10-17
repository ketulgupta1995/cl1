%{

#include<stdio.h>
#include "y.tab.h"

%}


digit [0-9]
integer {digit}+
letter [A-Za-z]
identifier {letter}({letter}|{integer})*

main main\(\)
header #include<.*>

%%
{header} {printf("lex h\n");return (HEADER);}
{main} {printf("lex main\n");return (MAIN);}

int|char {printf("lex var\n");return (VAR);}
\= {printf("lex =\n");return (ASSIG);}
\+|\-|\< {printf("lex Ari\n");return (ARITH);}
\; {printf("lex ;\n");return (ENDL);}
\n ;
(printf|scanf) {printf("lex func\n");return (FUNC);}
\( {printf("lex ob\n");return (OB);}
\) {printf("lex cb\n");return (CB);}
(\".*\") {printf("lex args\n");return (ARGS);}

("if"|"else") {printf("lex if\n");return (IF);}
("while")    {printf("lex wile\n");return (WHILE);}
\{ {printf("lex sb\n"); return (SB);}
\} {printf("lex eb\n");return (EB);}


{integer} return (INTEGER);
{identifier} {printf("identifier");return (IDENTIFIER);}

%%

int yywrap()
{

return 1;
}



%{
#include<stdio.h>
%}

header #include<.*>
main main\(\)
digit [0-9]
integer {digit}+
letter [A-Za-z]
identifier {letter}({letter}|{integer})*
%%

{header} {printf("header file : %s\n",yytext);}
int|char|float|string {printf ("variable detected: %s\n",yytext);}
{main} {printf("main function : %s\n",yytext);}
[\{]  {printf("Start of block\n");}
[\}]  {printf("end of block\n");}
("printf"|"scanf") {printf ("function statement detected: %s\n",yytext);}
"for" {printf("for loop detected: %s\n",yytext);}
"while" {printf("while loop detected: %s\n",yytext);}
{identifier} {printf("identifier : %s\n",yytext);}
[\;\n] ;
\( {printf("agru begin: %s",yytext);}
\) {printf("agru end: %s",yytext);}

\"({identifier}|\,|" ")*\" {printf("String arguments: %s",yytext);}
(\/\*(.*|\n)*\*\/|\/\/.*)  {printf("comments");}
%%

int yywrap(){
return 1;
}

void main(){
yyin=fopen("123.txt","r");
yylex();
}

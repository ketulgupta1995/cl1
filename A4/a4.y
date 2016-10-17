%{

#include<stdio.h>
#include<stdlib.h>
extern FILE* yyin;
%}


%token HEADER MAIN VAR ASSIG ARITH ENDL FUNC OB CB ARGS IF WHILE SB EB CALLB INTEGER IDENTIFIER

%%
S:Head mainl SB Stats EB {printf("==========CORRECT PROGRAM\n"); };
mainl: VAR MAIN    {printf ("==========main loop\n");};
Head: HEADER Head|HEADER {printf("==========Headers\n"); };
Stats : stat Stats{printf("==========Stats 1\n"); };|stat{printf("==========Stats 2\n"); }; 
stat : expr {printf("==========Stat exp\n"); };| FUNC OB ARGS CB ENDL {printf("==========func\n"); }; | IF OB cond CB SB Stats EB {printf("==========if\n"); };| WHILE OB cond CB SB Stats EB  {printf("==========whiel\n"); };
expr : VAR IDENTIFIER ENDL {printf("==========var a;\n"); };| IDENTIFIER ASSIG INTEGER ENDL {printf("==========expr a=2;\n"); };|IDENTIFIER ASSIG IDENTIFIER ENDL {printf("==========a=a+a\n"); };
cond : IDENTIFIER ARITH IDENTIFIER {printf("==========cond\n"); };|IDENTIFIER ARITH INTEGER {printf("==========cond2\n"); };
%%

void yyerror(char * s)
{
printf("==========SORRY\n");
}


void main()
{
yyin = fopen ("123.txt","r");
yyparse();

}

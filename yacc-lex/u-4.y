%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char* str);
%}

%union {
    char *str;
}


%token VARIABLE

%%

stmt: expr '\n' {
        printf("\n(1) \n");
    }
    | stmt expr '\n'{
        printf("\n(2) \n");
    }
    ;

expr :  expr '+' expr { printf("+ ");}
    |   expr '-' expr { printf("- ");}
    |   expr '*' expr { printf("* ");}
    |   expr '/' expr { printf("/ ");}
    |   '(' expr ')'
    | VARIABLE        { printf("%s ", yylval.str); }
    ;

%%

int main()
{
    yyparse();
    return 0;
}

void yyerror(char* str)
{
    printf("%s\n", str);
}

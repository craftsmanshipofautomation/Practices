%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "strlist.h"
#include <stddef.h>

void yyerror (char const *s);
int yylex();


%}
%union {
    char *str;
}

%token VAR
%token OP
%left '-' '+'
%left '*' '/'


%%

expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | VAR
    ;

%%

void yyerror (char const *s) {
   printf("%s\n", s);
}

int main()
{
    yyparse();
    return 0;
}
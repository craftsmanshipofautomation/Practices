%{
#include <stdio.h>
#include <string.h>
#include <assert.h>


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

%type <char*> expression
%type <char*> OP

%%

expression: expression OP expression { }
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
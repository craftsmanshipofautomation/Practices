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
%type <char*> 

%%

statement: expression;

expression: expression OP expression { $$.str = fucking_concat(fucking_concat($1.str, $3.str), $2.str);}
    | VAR { $$.str = $1.str; }
    ;

%%
// I hate c language
char * fucking_concat(char *s1, char* s2)
{
    assert(s1);
    assert(s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *new_shit = malloc(sizeof (char) * (len1 + len2 + 1));
    strcpy(new_shit, s1);
    strcat(new_shit, s2);
    free(s1);
    free(s2);
    return new_shit;
}

void yyerror (char const *s) {
   printf("%s\n", s);
}

int main()
{
    yyparse();
    return 0;
}
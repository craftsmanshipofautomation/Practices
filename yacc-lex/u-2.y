%{
#include "ch3hdr.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "libc.h"
void yyerror (char const *s);
int yylex();
%}

%union {
    double dval;
    struct symtab *symp;
}

%token <symp> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression

%%

statement_list: statement '\n'
    {
        lzlog("statement \n", s);    
    }
    |   statement_list statement '\n'
    {
        lzlog("statement_list statement \n", s);    
    }
    ;

statement : NAME '=' expression { $1->value = $3; }
    | expression    { printf("= %g\n", $1);}
    ;

expression: expression '+' expression   {$$ = $1 + $3;}
        |   expression '-' expression   {$$ = $1 - $3;}
        |   expression '*' expression   {$$ = $1 * $3;}
        |   expression '/' expression
            {
                if ($3 == 0.0)
                {
                    yyerror("divided by zero");
                }
                else
                {
                    $$ = $1 / $3;
                }
            }
        | '-' expression %prec UMINUS  {$$ = -$2;}
        | '(' expression ')'    {$$ = $2;}
        | NUMBER
        | NAME  {$$ = $1->value;}
        ;

%%


struct symtab *
symlook(char *s)
{
    char *p;
    struct symtab *sp;
    for (sp = symtab; sp < &symtab[NSYMS]; ++sp)
    {
        if (sp->name && !strcmp(sp->name, s))
            return sp;
        if (!sp->name)
        {
            sp->name = strdup(s);
            return sp;
        }
    }
    yyerror("TOO MANY SYMBOLS");
    exit(1);
}

void addfunc(char *name, double (*func)())
{
    struct symtab *sp = symlook(name);
    sp->funcptr = func;
}

int main()
{
    addfunc("sqrt", sqrt);
    addfunc("exp", exp);
    addfunc("log", log);
    yyparse();
}


void yyerror (char const *s) {
   printf("%s\n", s);
}
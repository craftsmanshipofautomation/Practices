%{
    #include <stdio.h>
double vbltable[26];
int yylex();
int yyerror(char *);
%}

%union {
    double dval;
    int vblno;
}

%token <vblno> NAME
%token <dval> NUMBER

%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression

%%

statement_list: statement '\n'
    |   statement_list statement '\n'
    ;

statement : NAME '=' expression { vbltable[$1] = $3; }
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
        | NAME  {$$ = vbltable[$1];}
        ;

%%

int yyerror(char *msg)
{
    printf("%s\n", msg);
    return 0;
}

int main()
{
    yylex();
}


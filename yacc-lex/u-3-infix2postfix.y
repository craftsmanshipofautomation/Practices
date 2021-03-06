%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "strlist.h"
#include "libc.h"

void yyerror (char const *s);
int yylex();


%}
%union {
    struct list_head* list;
    char *str;
}

%token VAR
%token OP1
%token OP2

%left OP1
%left OP2

%type <list> expr
%type <str> OP1
%type <str> OP2
%type <str> VAR



%%

statement: expr '\n'
    {
        lzlog("statement", s);
        sl_show($1);
        sl_free($1);
    }
    | statement expr '\n'
    {
        lzlog("statement expr", s);
        sl_show($2);
        sl_free($2);
    }
    ;

expr: expr OP1 expr
    {
        lzlog("op1", s);
        struct list_head* lhs = $1, *rhs = $3;
        char *op = $2;
        int len = sl_length(lhs);
        //lzlog(len, d);
        //sl_show(lhs);
        //sl_show(rhs);
        sl_concat(lhs, rhs);
        sl_append(lhs, op);
        //sl_show(lhs);
        $$ = lhs;
        //sl_show(&($$));
        free(op);

    }
    | expr OP2 expr
    {
        lzlog("op2", s);
        struct list_head* lhs = $1, *rhs = $3;
        char *op = $2;
        //sl_show(lhs);
        //sl_show(rhs);
        sl_concat(lhs, rhs);
        sl_append(lhs, op);
        $$ = lhs;
        //sl_show(lhs);
        free(op);
    }
    | VAR
    {
        lzlog($1, s);
        struct list_head* var = sl_malloc();
        sl_append(var, $1);
        $$ = var;
        //sl_show(var);
        free($1);
    }
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
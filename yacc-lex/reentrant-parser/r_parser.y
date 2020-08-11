/* things to generate */
%output  "r_parser.c"
%defines "r_parser.h"

%code top{
/* put this on the top of the generated code */
/* use bussiness code */
#include "r.h"
#include "r_parser.h"
#include "r_scanner.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
#endif

/* boilerplates that share the same parameters used by yyparse */
int yyerror(struct r_ctx* bw, void * scanner, const char *msg) {
    (void)bw;
    (void)scanner;
    (void)msg;
    return 0;
}

}

%initial-action {
}

//%define api.prefix {r_}
%define api.pure full
%lex-param   { scanner }
%parse-param { struct r_ctx* ctx }
%parse-param { void * scanner }
%debug

%union {
    char* str;
    int number;
}

/* specific tokens to be use    */
%token ADD DEL DEV
/* declare some tokens' type    */
%token <str> STRING IPCMDTYPE ADDRESS_STRING
%token <number> NUMBER
/* declare non-terminals' type  */

%%

IPADDRCMD :
    {
        ctx->error = -1;
    }
    | HEADER OPERATION ADDRESS DEVICE
    {
        ctx->error = 0;
    }
    ;

HEADER: IPCMDTYPE
    ;

DEVICE: DEV STRING
    {
        ctx->dev = $2;
    }
    ;

OPERATION: ADD {
        ctx->op = RADD;
    }
    | DEL {
        ctx->op = RDEL;
    }
    ;

ADDRESS: ADDRESS_STRING
    {
        ctx->addr = $1;
    }
    ;

%%


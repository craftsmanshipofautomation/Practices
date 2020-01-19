%{
#include "u-4.h"
#include <string.h>
%}

%option noyywrap

%%

[A-Za-z0-9]* {
    yylval.str = strdup(yytext);
    return VARIABLE;
}
[ \t] ;
\n  |
.   { return yytext[0];}

%%

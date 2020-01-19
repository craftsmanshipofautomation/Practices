%{
#include "u-4.tab.h"
#include <string.h>
%}

%%

[A-Za-z0-9]* {
    yylval.str = strdup(yytext);
    return VARIABLE;
}
[ \t] ;
\n  |
.   { return yytext[0];}

%%

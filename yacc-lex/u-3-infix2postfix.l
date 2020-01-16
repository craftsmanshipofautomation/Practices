%{
#include "u-3-infix2postfix.tab.h"
#include <string.h>
%}



%%
tgygh
list








[A-Za-z][A-Za-z0-9]* { 
    yylval.str = strdup(yytext);
    return VAR;
}

[\-\+\*/] {
    yylval.str = strdup(yytext);
    return OP;
}

[ \t]   ;

\n | .   return yytext[0];

%%
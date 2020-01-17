%{
#include "strlist.h"
#include "u-3-infix2postfix.tab.h"
#include <string.h>
#include "libc.h"
%}

%%

[A-Za-z0-9]* { 
    yylval.str = strdup(yytext);
    return VAR;
}

[-|+] {
    yylval.str = strdup(yytext);
    return OP1;
}

[*|/] {
    yylval.str = strdup(yytext);
    return OP2;
}

\n {
    return 0;
}

%%

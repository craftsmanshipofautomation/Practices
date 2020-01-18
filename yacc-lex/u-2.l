%{
#include "u-2.tab.h"
#include "ch3hdr.h"
#include <math.h>

void numform_dump(char*);
%}

%%

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
        yylval.dval = atof(yytext);
        return NUMBER;
    }
[ \t]   ;
[A-Za-z][A-Za-z0-9]* { 
    struct symtab *sp = symlook(yytext)    ;
    yylval.symp = sp;
    return NAME;
}

"$" {return 0;}
\n | .   { numform_dump(yytext); return yytext[0];}
%%

void numform_dump(char* str)
{
    int s = strlen(str);
    int i;
    for (i = 0; i < s; ++i)
    {
        printf("%d ", str[i]);
    }
    printf("\n");

}

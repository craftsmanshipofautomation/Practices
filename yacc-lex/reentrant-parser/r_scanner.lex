/* specific what files to be generated */
%option outfile="r_scanner.c" header-file="r_scanner.h"
%option reentrant
%option bison-bridge
%option bison-locations
%option noinput
%option nounput
%option noyywrap
%option prefix="r_"
%option yylineno
%option debug

%{
/* use business code */
#include "r.h"
/* use definitions of tokens */
#include "r_parser.h"

%}

digit       [0-9]
alpha       [a-zA-Z]
char        ({digit}|{alpha})+

%%

ip              return IP;
address         return ADDRESS;
add             return ADD;
del             return DEL;
dev             return DEV;
{digit}{1,3}\.{digit}{1,3}\.{digit}{1,3}\.{digit}{1,3}\/{digit}{1,2}
                {
                    yylval->str = strdup(yytext);
                    return STRING;
                }
{char}+         {
                    yylval->str = strdup(yytext);
                    return STRING;
                }
[ \t\r\n] {
    /*do nothing*/
}
. {
    // JUNK
}
%%

// boilerplate that I have no idea how it works
void scanner_destroy(void *scanner)
{
    yypop_buffer_state(scanner);
    yylex_destroy(scanner);
}

// use the scanner to split the tokens
void scanner_push_buffer(void* scanner, const char *buffer)
{
    YY_BUFFER_STATE b;
    b = yy_scan_string(buffer, scanner);
    assert(b != NULL);
    return;
}





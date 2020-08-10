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
// 引用 r 接口
#include "r.h"
// 引用 yacc 生成的接口
#include "r_parser.h"

static void update_location(struct location* loc, char* text, unsigned int lineno,
    unsigned int column)
{

    loc->first_line = loc->last_line;
    loc->first_column = loc->last_column;
    loc->last_line = lineno;
    loc->last_column = column;
    loc->token = text;
}

#define YY_USER_ACTION                  \
{                                       \
    update_location(yylloc, yytext,     \
    yylineno, yycolumn);                \
    yycolumn += yyleng;                 \
}


%}

ASC     [\x00-\x7f]
ASCN    [\x00-\t\v-\x7f]
U       [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]
UANY    {ASC}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANYN   {ASCN}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UONLY   {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
GOOD_ASC    [\x21-\x7e]

digit   [0-9]
alpha   [a-zA-Z_]
char  ({digit}|{UONLY}|{GOOD_ASC})
integer  -?({digit}+)

%%

ip          return IP;
address     return ADDRESS;
add         return ADD;
del         return DEL;
dev         return DEV_PREDICATOR;




add             return ADD;
set             return SET;
del             return DEL;
clear           return CLEAR;
check           return CHECK;
startup         return STARTUP;
download        return DOWNLOAD;
refresh         return REFRESH;
help            return HELP;
dynamic         return DYNAMIC;
f               return F;
s               return S;
family          return FAMILY;
name            return NAME;
srcip           return SRCIP;
dstip           return DSTIP;
iif             return IIF;
oif             return OIF;
time            return TIME;
qos             return QOS;
service         return SERVICE;
bandwidth       return BANDWIDTH;
host            return HOST;
forward         return FORWARD;
backward        return BACKWARD;
active          return ACTIVE;
comment         return COMMENT;
all             return ALL;
newid           return NEWID;
id              return ID;
version         return VERSION;
(ipv4|ipv6|IPV4|IPV6) {
                    yylval->number = yytext[3] - '0';
                    return NUMBER;
                }
(on|ON)         {
                    yylval->number = 1;
                    return NUMBER;
                }
(off|OFF)       {
                    yylval->number = 0;
                    return NUMBER;
                }
{integer}       {
                    yylval->number = atoi(yytext);
                    return NUMBER;
                }
{char}+         {
                    yylval->str = xstrdup(yytext);
                    return STRING;
                }
[ \t\r\n] {
    /*do nothing*/
}
. {
    // JUNK
}
%%

void scanner_destroy(void *scanner)
{
    yypop_buffer_state(scanner);
    yylex_destroy(scanner);
}

void scanner_push_buffer(void* scanner, const char *buffer)
{
    YY_BUFFER_STATE b;
    b = yy_scan_string(buffer, scanner);
    assert(b != NULL);
    return;
}





%output  "bw_parser.c"
%defines "bw_parser.h"

%code top{
#include "bw.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
#endif

int bw_error(void *location, struct bw_ctx* bw, void * scanner, struct bw_state* state, const char *msg) {
    (void)bw;
    (void)scanner;
    (void)state;
    struct location * loc = (struct location*)location;
    ez_debug("[%s]:%d:%d:%s\n",
        msg, loc->first_line, loc->first_column,
        loc->token);
    return 0;
}

extern int bw_lex(void*, void*, void*);
extern int bw_lex_init(void*);
extern void bw_set_debug(int, void*);

static void location_init(void *loc)
{
    memset(loc, 0, sizeof(struct location));
}

}

%initial-action {
    location_init(&yylloc);
}

%name-prefix "bw_"
%define api.pure full
%lex-param   { scanner }
%parse-param { struct bw_ctx* bw }
%parse-param { void * scanner }
%parse-param { struct bw_state * state }
%locations
%debug

%union {
    char* str;
    struct bw_optpair *pair;
    struct list_head* list;
    struct bwrule* rule;
    int number;
}

%token ADD SET MOVE DEL CLEAR CHECK STARTUP DOWNLOAD REFRESH HELP DYNAMIC VERSION S
%token FAMILY NAME SRCIP DSTIP IIF OIF F
%token TIME QOS SERVICE BANDWIDTH HOST FORWARD BACKWARD
%token ACTIVE COMMENT ALL ID NEWID

%token <str> STRING
%token <number> NUMBER
%type <list> properties
%type <pair> pair
%type <number> number_keyword  string_keyword loner
%type <number> operation intransive_verb triple double


%%

bw: {
        state->error = -1;
    }
    | operation properties
    {
        struct bwrule* rule = bwrule_new();
        bwrule_init(rule, $2);
        state->rule = rule;
        state->op = $1;
    }
    | intransive_verb {
        struct bwrule* rule = bwrule_new();
        state->rule = rule;
        state->op = $1;
    }
    | triple NUMBER NUMBER {
        struct bwrule* rule = bwrule_new();
        state->rule = rule;
        state->op = $1;
        state->_1 = $2;
        state->_2 = $3;
    }
    | double STRING {
        struct bwrule* rule = bwrule_new();
        state->rule = rule;
        state->op = $1;
        state->_3 = $2;
    }
    | unrecognized {
        state->error = -1;
    }
    ;

operation: ADD {
        $$ = BWADD;
    }
    | SET {
        $$ = BWSET;
    }
    | MOVE {
        $$ = BWMOVE;
    }
    | DEL {
        $$ = BWDEL;
    }
    ;

intransive_verb: STARTUP {
        $$ = BWSTARTUP;
    }
    | CLEAR {
        $$ = BWCLEAR;
    }
    | CHECK {
        $$ = BWCHECK;
    }
    | REFRESH {
        $$ = BWREFRESH;
    }
    | HELP {
        $$ = BWHELP;
    }
    | DOWNLOAD {
        $$ = BWDOWNLOAD;
    }
    | VERSION {
        $$ = BWVERSION;
    }
    | S {
        $$ = BWCONNTRACKMODULERELOAD;
    }
    ;

triple: DYNAMIC {
        $$ = BWDYNAMIC;
    }
    ;

double: F {
        $$ = BWF;
    }
    ;

unrecognized : NUMBER
    |   STRING
    | unrecognized unrecognized
    ;

properties: pair
    {
        $$ = xmalloc(sizeof(*$$));
        INIT_LIST_HEAD($$);
        list_add_tail(&($1->list), $$);
    }
    | properties pair
    {
        $$ = $1;
        list_add_tail(&($2->list), $$);
    }
    ;

pair: string_keyword STRING
    {
        $$ = bw_optpair_new_from_string($1, $2);
        ez_debug("[1] %d: %s\n", $1, $2);
    }
    | string_keyword NUMBER
    {
        char buf[256];
        char* p;
        ZEROIZE(buf);
        snprintf(buf, sizeof(buf), "%d", $2);
        p = strdup(buf);
        $$ = bw_optpair_new_from_string($1, p);
        ez_debug("[1] %d: %s\n", $1, p);
    }
    | number_keyword NUMBER
    {
        $$ = bw_optpair_new_from_number($1, $2);
        ez_debug("[2] %d: %d\n", $1, $2);
    }
    | loner
    {
        $$ = bw_optpair_new_from_number($1, 1);
        ez_debug("[3] %d: %d\n", $1, 1);
    }
    ;

string_keyword: NAME { $$ = BWOPT_NAME; }
    | SRCIP { $$ = BWOPT_SRCIP; }
    | DSTIP { $$ = BWOPT_DSTIP; }
    | IIF { $$ = BWOPT_IIF; }
    | OIF { $$ = BWOPT_OIF; }
    | TIME { $$ = BWOPT_TIME; }
    | SERVICE { $$ = BWOPT_SERVICE; }
    | BANDWIDTH { $$ = BWOPT_BANDWIDTH; }
    | COMMENT { $$ = BWOPT_COMMENT; }
    ;

number_keyword: FAMILY { $$ = BWOPT_FAMILY; }
    | QOS { $$ = BWOPT_QOS;}
    | HOST { $$ = BWOPT_HOST; }
    | ACTIVE { $$ = BWOPT_ACTIVE; }
    | FORWARD { $$ = BWOPT_FORWARD; }
    | BACKWARD { $$ = BWOPT_BACKWARD; }
    | ID { $$ = BWOPT_ID; }
    | NEWID {$$ = BWOPT_NEWID; }
    ;

loner: ALL { $$ = BWOPT_ALL; }
    ;

%%


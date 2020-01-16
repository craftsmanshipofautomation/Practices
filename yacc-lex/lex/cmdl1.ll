%{
#include "defines.h"
int verbose;
char *progname;

int myinput(char *buf, int max);
#undef YY_INPUT
#define YY_INPUT(buf, result, max) (result = myinput(buf, max))

%}

%%
-h |
--help |
-? {
    printf("no help available\n");
}
-v |
--verbose {
    verbose = 1;
    printf("verbose mode on\n");
}
. ;

%%

char **targv;
char **arglim;

void use(int argc, char** argv)
{
    printf("argc: %d\n", argc);
    progname = *argv;
    targv = argv + 1;
    arglim = argv + argc;
    yylex();
}

int myinput(char* buf, int max)
{
    printf("max len to buf: %d\n", max);
    if (targv >= arglim)
    {
        printf("targv >= arglim\n");
        return 0;
    }
    int len;
    len = strlen(*targv);
    memcpy(buf, *targv, len);
    buf[len] = ' ';
    ++ len;
    ++ targv;
    return len;
}



#ifndef R_H
#define R_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

enum {
    RADD,
    RDEL
};

struct r_ctx
{
    char* addr;
    char* dev;
    int op;
    int error;
};

int r_run_cmd_from_buffer(struct r_ctx* ctx, char* buf);
struct r_ctx* r_ctx_new();
void r_ctx_delete(struct r_ctx*);



#endif
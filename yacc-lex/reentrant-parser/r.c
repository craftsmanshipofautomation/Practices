#include "r.h"

int main(int argc, char *argv[])
{
    struct r_ctx *ctx;
    char *buf = NULL;
    int len, i, rc;
    /// copy argv into buf
    for (len = 0, i = 1; i < argc; ++i)
        len += strlen(argv[i]) + strlen(" ");
    buf = calloc(1, len);
    if (buf == NULL)
    {
        exit(-1);
    }
    for (i = 1; i < argc; ++i)
    {
        strcat(buf, argv[i]);
        if (i + 1 < argc)
            strcat(buf, " ");
    }
    /// matter of buf finishes
    ctx = r_ctx_new();
    rc = r_run_cmd_from_buffer(ctx, buf);
    r_ctx_delete(ctx);
    free(buf);

    return rc;
}
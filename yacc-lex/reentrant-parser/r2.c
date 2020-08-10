#include "r.h"

struct r_ctx* r_ctx_new()
{
    struct r_ctx* p = calloc(1, sizeof(struct r_ctx));
    return p;
}

void r_ctx_delete(struct r_ctx* ctx)
{
    free(ctx->addr);
    free(ctx->dev);
    free(ctx);
}

int r_run_cmd_from_buffer(struct r_ctx* ctx, char* buf)
{
    if (ctx->error)
        printf("dead wrong\n");
    if (ctx->addr)
        printf("address: %s\n", ctx->addr);
    if (ctx->dev)
        printf("interface: %s\n", ctx->dev);
    printf("operation: %s\n", ctx->op == RADD ? "add" : (ctx->op == RDEL ? "del": "UB"));

}

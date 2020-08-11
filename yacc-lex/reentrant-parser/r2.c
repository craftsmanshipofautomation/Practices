#include "r.h"
#include "r_parser.h"
#include "r_scanner.h"

extern void scanner_destroy(void *scanner);
extern void scanner_push_buffer(void* scanner, const char *buffer);

struct r_ctx* r_ctx_new()
{
    struct r_ctx* p = calloc(1, sizeof(struct r_ctx));
    p->scanner = scanner_init();
    return p;
}

void r_ctx_delete(struct r_ctx* ctx)
{
    scanner_destroy(ctx->scanner);
    free(ctx->addr);
    free(ctx->dev);
    free(ctx);
}

void * scanner_init(void)
{
    void *scanner;
    r_lex_init(&scanner);
    return scanner;
}

int r_run_cmd_from_buffer(struct r_ctx* ctx, char* buf)
{
    const char* s;

    scanner_push_buffer(ctx->scanner, buf);
    r_parse(ctx, ctx->scanner);


    if (ctx->error)
        printf("dead wrong\n");
    if (ctx->addr)
        printf("address: %s\n", ctx->addr);
    if (ctx->dev)
        printf("interface: %s\n", ctx->dev);
    switch (ctx->op)
    {
        case RNOOP:
            s = "no-op";
            break;
        case RADD:
            s = "add";
            break;
        case RDEL:
            s = "del";
            break;
    }
    printf("operation: %s\n", s);

}

%{
void ban(char *, int);
int count = 0;
%}
%pointer
%%

"zap me"

%%
void ban(char *src, int len)
{
    int i = 0;
    for (; i < len; ++i)
        src[i] = '1';
}

int main(int argc, char** argv)
{
    yylex();
}
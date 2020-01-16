%{
int line_cnt = 0;
int word_cnt = 0;
int char_cnt = 0;
int whitespace_cnt = 0;
#define pint(num) printf(#num": %d\n", num);

%}
%%
\n      { ++line_cnt; }
<<EOF>> { ++line_cnt; return 0;}
[\t ]   { ++whitespace_cnt;}
[^\t \n]+ {++word_cnt; char_cnt += yyleng;}


%%

int main(int argc, char** argv)
{
    FILE* file;
    file = fopen(argv[1], "r");
    yyin = file;
    yylex();
    pint(line_cnt);
    pint(word_cnt);
    pint(char_cnt);
    pint(whitespace_cnt);

}


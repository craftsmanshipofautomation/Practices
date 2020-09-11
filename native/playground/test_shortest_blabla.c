#include "libc.h"
char *shortestPalindrome(char *s)
{
    int len = strlen(s);
    int max = len - 1;
    int mid = (len - 1) / 2;
    int curr = mid;
    char *result = 0;
    int rlen1 = INT_MAX;
    int rlen2 = INT_MAX;
    int hit1 = 0;
    int hit2 = 0;
    int mid_summers_eve1 = 0;
    int mid_summers_eve2 = 0;
    int offset = 0;
    int quit = 0;
    if (!len)
        return calloc(1, sizeof(char));
    while (curr > -1)
    {
        offset = 0;
        hit2 = 0;
        // 无中轴线
        while (curr - offset > -1 && curr + 1 + offset < len &&
               (curr + 1) * 2 < len + 1)
        {
            if (s[curr - offset] == s[curr + 1 + offset])
            {
                ++hit2;
                ++offset;
            }
            else
                break;
        }
        if (hit2 && hit2 == (curr + 1))
        {
            rlen2 = (max - curr) * 2;
            mid_summers_eve2 = curr;
            quit = 1;
        }
        else
        {
            rlen2 = len * 2;
            mid_summers_eve2 = -1;
        }

        if (quit)
            break;

        offset = 0;
        hit1 = 0;
        // 有中轴线
        while (curr - 1 - offset > -1 && curr + 1 + offset < len)
        {
            if (s[curr - 1 - offset] == s[curr + 1 + offset])
            {
                ++hit1;
                ++offset;
            }
            else
                break;
        }
        // 匹配数等于索引
        if (hit1 && hit1 == curr)
        {
            mid_summers_eve1 = curr;
            rlen1 = (max - curr) * 2 + 1;
            quit = 1;
        }
        else
        {
            rlen1 = (len - 1) * 2 + 1;
        }
        if (quit)
            break;

        --curr;
    }

    if (rlen1 > rlen2)
    {
        result = malloc(sizeof(char) * rlen2 + 1);
        curr = (rlen2 - 1) / 2;
        offset = 0;
        while (curr + 1 + offset < rlen2)
        {
            result[curr - offset] = s[mid_summers_eve2 + 1 + offset];
            result[curr + 1 + offset] = s[mid_summers_eve2 + 1 + offset];
            ++offset;
        }
        result[rlen2] = '\0';
    }
    else
    {
        result = malloc(sizeof(char) * rlen1 + 1);
        curr = rlen1 / 2;
        offset = 0;
        while (curr + offset < rlen1)
        {
            result[curr - offset] = s[mid_summers_eve1 + offset];
            result[curr + offset] = s[mid_summers_eve1 + offset];
            ++offset;
        }
        result[rlen1] = '\0';
    }

    return result;
}

int main()
{
    const char *s = "evpajhxgqfkjhsdzqpbeaoxkhgrgtqokplcitwcstlpgeioeiuyxyjhcze"
                    "zxpqwdcljgptklvipzrhlegxtioavmnxwbqbjtuyrf"
                    "kthwgcsvgkitdwuizxvhaybkvwnavgnivfztbmrxfyfgjuyrhpibqkqbee"
                    "jdqfbtgpalarqqpbcviotqnlnxiorrcpkdcggwrjpo"
                    "hfikahrafavgaisfleaxxxmfhceylbfwqdcykoeddwoflslmhjmokrbcyo"
                    "tfyztaffxxdrfnkfgpggvzteebddoyrhemwroobkch"
                    "kqpxvcfouzgmsgzbgqbeyvbtrybcnowzacwizvdqoqvlvczerdtvtscntv"
                    "purwolkmrrjsphlpilslqzaoxwhsmxgweyusxdveaa"
                    "iiifewpakazxgasypfubfcxfavxpdvotyvbfryhagftrppjhzfsbinspfu"
                    "cyuwwavffuejldqjeytyvqrmicfkewqmtnewnynfka"
                    "fofrzqqrfnojdwztuiuidwwibfeqzdecjxegccedeorzsefgedjtxjsipo"
                    "ytclkwzmqgdjgdmpfcclpqiaewfctdqrqzddgrwnwk"
                    "bnaiblujzewezinxkcvbvtyfbkvwmqxqyetxmmscqnjqhheicgxfypevon"
                    "wajblvvcwyqzuniqyvxicoycfpiuxzvzjsvcarlgiv"
                    "spexmmjshiywcybffxzawovnxdrnzxkynjwmwmhkvacmautvayiqkcvtiq"
                    "zoeuaoqiwknhuxkezqoeryruqxisqnspeblyhfjcts"
                    "wlwbkpgbznfebbzzcstuzgitjplsknwxxzvpulikkhynxoegwgkowxiapf"
                    "qbmqlpqkgqlalnuiowacdrqoaoclgqsfneeotdgqni"
                    "xfqifbuwwjrelmgjikwcxgomuqmaubcsotxeogakwtoysjefxzqwfbofjb"
                    "babavsldeyhfxemofhzsgobsfjyrkngupdsdmbwkgg"
                    "gylcsrwizleghcpbpdczfqafolzglvjhoabytvpwjxkvyomdsijpmjsirh"
                    "fyykjtpqdhxpbyjepvobwvxgvtxyhglhzcnafuuwkm"
                    "vadnberqxandklgnomefutcknwaxrdgivzgbwlaxyxncamyqpbgujgerax"
                    "vxcqfeufocguaspcdeverfuozjohtrqpfpigoeggdg"
                    "zsxnmadodmkqhemdyxlzymtfliwqmezodadjacjpwldekzapmfwymdyfil"
                    "stdlvmexlfdjobqyuskkrxsbosbllmzavxflpfxlbm"
                    "qnuygvgbhghbkfccbqbvryoynesofwrdketjblvkqdbgrfakdzvuxfimci"
                    "cwldprvqwtvhppcedqiaucbuktcrlmbgamtohlsedq"
                    "jlxxvlnqylhqjcfakeazposusgbhboulvcguhqlyvqgvynmvshzqwgbzkb"
                    "wtxonmkxdmxxmdlnbruokrcswrhzpxmkuwtgnssnvt";
    char *result = shortestPalindrome(s);
    printf("%s\n", result);
    free(result);
}

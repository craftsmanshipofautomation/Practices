#include "libcxx.h"
using namespace std;

vector<int> kmp(string &src, string pat)
{
    vector<int> ret;
    int si = 0, pi;
    while (si < src.size() - pat.size())
    {
        pi = 0;
        if (src[si] == pat[pi])
        {
            do
            {
                ++si;
                ++pi;
            } while (src[si] == pat[pi]);
            if (pi == pat.size())
                ret.push_back(si - pi);
        }
        else
            ++si;
    }
    return ret;
}

vector<int> match(string &src, string pat)
{
    vector<int> ret;
    int si = 0, pi, ci, space;
    while (si < src.size() - pat.size())
    {
        pi = 0;
        ci = si;
        space = 0;
        if (src[si] == pat[pi])
        {
            do
            {
                ++ci;
                while (src[ci] == ' ')
                {
                    ++ci;
                    ++space;
                } 
                ++pi;
            } while (src[ci] == pat[pi]);
            if (pi == pat.size())
                ret.push_back(ci - pi - space);
        }
        ++si;
    }
    return ret;
}

int main()
{
    string src = "Abb bca acb                   bd";
    string pat = "bb";
    auto r1 = kmp(src, pat);
    auto r2 = match(src, pat);
    print(r1);
    print(r2);
}

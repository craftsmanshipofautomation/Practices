#include "libc.h"

int lengthOfLongestSubstring(char* s) 
{
    if (*s == '\0')
    {
        return 0;
    }
    char* start_point = s;
    char* pioneer = start_point;
    int record[128] = {0};
    int maxlen = 1, dynlen = 1;
    record[*start_point] = 1;
    while (*pioneer != '\0')
    {
        // pioneer walks
        while (*pioneer != '\0')
        {
            ++pioneer;
            ++record[*pioneer];
            ++dynlen;
            if (record[*pioneer] > 1)
            {
                break;
            }
        } 
        // 
        maxlen = maxlen > dynlen-1 ? maxlen : dynlen-1;
        
        while (start_point < pioneer && record[*pioneer] > 1)
        {
            // clear record
            --record[*start_point];
            ++start_point;
            --dynlen;
        };
        
    }
    return maxlen;
}
    

int main()
{
}

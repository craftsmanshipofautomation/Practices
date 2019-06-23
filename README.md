
## **Table of Contents**
- [Project Structure](#project-structure)
    - [Makefile](#makefile)

-------

## Project Structure

`lib/`, as its name suggests, serves as library code, for the sake of convenience, both C and C++ functions goes there, but are built into 2 different shared library, namely `lib_c.so` and `lib_cxx.so`.

Codes on some directories depend heavily on the 2 lib, such like `test`, `leetcode`, `interview`.

Some are independent, their reason to stay in this repository is to avoid pollution of my github. They are to be taken way, handed over, such like offline-interview questions which interviewers ask you to finish at home, and some mercenary work, such as school homework those college students do not wish to do.~~(every coin counts before you get a job)~~.

### Makefile

Makefile is written with [Explicit Path Method](http://make.mad-scientist.net/papers/multi-architecture-builds/#explicitpath). ~~(the advanced vpath method shall be employed one day)~~

## Things of interest

|Code|Description|
|--|--|
|[makefile](https://github.com/openswords/Practices/blob/master/makefile)|monsterous make|
|[24-point](https://github.com/openswords/Practices/blob/master/mercenary/24r.c)|the generic form of 24-point game|
|[next_combination](https://github.com/openswords/Practices/blob/master/lib/combination.cpp)|similar to next_permutation|
|[find the kth number](https://github.com/openswords/Practices/blob/master/interview/find-kth-largest-number-using-qsort.c)|its time complexity is O(n)|
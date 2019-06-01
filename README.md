## 1

`lib/` (provide basic functions)

Other directories collect executables relying on `lib/`

Some are independent, they have their own header and library, such as interview questions, and any other code that requires to hand over to other people, such code must not depend on `lib/`

Currently `lib` is a collection of both C and C++ functions, with no further classification, just for convenience.

## 2

I do not deliberately use English to comment or generally, write things; I do it because I don't want to install Chinese input method on my Ubuntu machine, so that I can save my time from pressing shift to get the right input method, you see :)

## The Design of Makefile

It is not like projects with many modules, because, for example, `leetcode` is not a module, the real modules will exist in `lib/`, if I still use this playground, days after.

The Design is to put a top level makefile in the root directory, to describe how to build `lib/` and other directories which rely on `lib/`, with lazy and brutal wildcards. The directories that are independent will have a makefile themselves, which will be included in the top-level makefile later.

In `lib/`, C++ headers use `.hpp` as extension as distinct from C `.h`.

Also, I will mark `*.o`, the intermediate files not to be deleted, so as to speed up compilation. The intermediate files will be generated in `out` directory, to keep the project sources clean.










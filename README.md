## 1

`lib/` (provide basic functions)

Other directories collect executables relying on `lib/`

Some are independent, they have their own header and library, such as interview questions, and any other code that requires to hand over to other people, such code must not depend on `lib/`

Currently `lib` is a collection of both C and C++ functions, with no further classification, just for convenience.

## 2

I do not deliberately use English to comment or generally, write things; I do it because I don't want to install Chinese input method on my Ubuntu machine, so that I can save my time from pressing shift to get the right input method, you see :)

## Structure

Makefile is written with [Explicit Path Method](http://make.mad-scientist.net/papers/multi-architecture-builds/#explicitpath). (**TODO: use advanced vpath some other day!**)

`lib/` is the place for common code, and will be used to build shared libraries. C and C++ libraries will built separately. `leetcode/` contains my solution to some leetcode problems. `test/` simply tests. `take-home/` is for codes to be submitted to other people, for interviews or mercenary works. Those codes will not integrate `lib/` libraries, and had better be placed in another repository, but I think it belongs to the practice category, also I want to keep my github clean. In the future, there will be more directories added for the same reason.

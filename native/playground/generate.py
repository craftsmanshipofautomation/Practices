#!/usr/bin/python3.6
import os

leetcode_cn_prefix = "https://leetcode-cn.com/problems/"
prefixes_to_rm = [leetcode_cn_prefix]

github_page_prefix = "https://github.com/openswords/Practices/tree/master/leetcode/"


def ReadConfig(fn):
    problems = []
    with open(fn, "r") as f:
       for line in f:
         line = line.strip()
         if line:
             items = line.split(",")
             items = [i.strip() for i in items]
             problems.append((items[0], items[1:]))
    return problems

def Process(problems):
    print(problems)
    with open("readme.md", "w") as md:
        md.write("|Problems|Solution|\n")
        md.write("|--|--|\n")
        for p, lang in problems:
            f = p
            for pref in prefixes_to_rm:
                f = f.replace(pref, "")
            f = f.replace("/", "")
            md.write("|[{pname}]({purl})|".format(pname=f, purl=p))
            for L in lang:
                sf = f + "." + L
                github_url = github_page_prefix + sf
                md.write("[{sname}]({surl})".format(sname=L, surl=github_url))
                md.write("   ")
            md.write("|\n")
            #exists = os.path.isfile(sf)
            # if not exists:
            #   with open(sf, "w") as new:
            #      if lang == c or lang == cpp:
            #         new.write('#include "libc.h"\n\n\n\n')
            #         new.write("int main()\n{\n}\n")
            #      if lang == py:
            #         new.write('if __name__ == "__main__":\n')


if __name__ == "__main__":
    problems = ReadConfig("problems.txt")
    Process(problems)

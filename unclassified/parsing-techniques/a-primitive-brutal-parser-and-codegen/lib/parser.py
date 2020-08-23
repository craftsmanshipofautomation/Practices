import re
import copy

def initClassMap(fn):
    GClassMap = {}
    with open(fn, "r") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line.startswith('#'):  # comment
                continue
            else:
                comment = line.find("#")
                if comment == -1:
                    pass
                else:
                    line = line[0:comment]
                eqIdx = line.find("=")
                clsn = line[0:eqIdx].strip()
                nick = line[eqIdx+1:].strip()
                GClassMap[clsn] = nick
    return GClassMap


class Helper(object):
    whiteSpace = ["\n", "\r", " ", "\b", "\t"]

    @staticmethod
    def splitByWhitespace(line):
        result = []
        wordStart = 0
        wordEnd = 0
        size = len(line)
        i = 0
        while 1:
            # move the word start, touches solid char
            while i < size and line[i] in Helper.whiteSpace:
                i += 1
            if i == size:
                break  # there shall be no more words
            wordStart = i
            i += 1
            # move the word end, touches white space
            while i < size and line[i] not in Helper.whiteSpace:
                i += 1
            wordEnd = i
            word = line[wordStart:wordEnd]
            result.append(word)
        return result

    @staticmethod
    def findOccurrence(lst, word):
        for i in lst:
            if i in word:
                return i
        return None

    @staticmethod
    def removeEmptyStrInList(lst):
        result = []
        for e in lst:
            if e:
                result.append(e)
        return result

    @staticmethod
    def ReplaceEmptyStrInList(lst, de):
        result = []
        for e in lst:
            if e:
                result.append(e)
            else:
                result.append(de)
        return result

    @staticmethod
    def split(spliter, line):
        """
        a:b -> a, b
        """
        result = Helper.splitByWhitespace(line)
        curr = 0
        while 1:
            size = len(result)
            nowWhat = result[curr]
            de = Helper.findOccurrence(spliter, nowWhat)
            if not de:
                curr += 1
            else:
                frags = Helper.removeEmptyStrInList(nowWhat.split(de))
                part1 = result[0:curr] if curr != 0 else []
                part2 = result[curr+1:]
                for f in frags:
                    part1.append(f)
                result = part1 + part2
                curr = 0
            if curr == size:
                break
        return result

    @staticmethod
    def takeApartWord(de, word):
        rest = word
        size = len(de)
        result = []
        while 1:
            if not rest:
                break
            r = rest.find(de)
            if r == -1:
                result.append(rest)
                break
            else:
                front = rest[0:r]
                mid = de
                rest = rest[r+size:]
                if front:
                    result.append(front)
                result.append(mid)
        return result

    @staticmethod
    def takeApartLine(delimiters, line):
        """
        a:b -> a, :,  b
        """
        fragments = Helper.splitByWhitespace(line)

        for de in delimiters:
            next_fragments = []
            for word in fragments:
                r = Helper.takeApartWord(de, word)
                next_fragments.extend(r)
            fragments = copy.deepcopy(next_fragments)
        return fragments


class Parser(object):
    """
    case ignorable render:
        ignorable function(args);
        break;

    1. split by whitespace
    2. split by delimiters
    """
    collection = []
    clsPat = re.compile(r"case\s+.*Effect\.Filter\.k(?P<clsName>\w+):")
    argsPat = re.compile(r"")
    delimiters = ["case", ":", "=", "(", ")", "{", "}", ",", ";"]

    FIND_EQUAL = 0
    FIND_STARTSWITH = 1
    FIND_ENDSWITH = 2

    @staticmethod
    def getClassName(line):
        result = Parser.clsPat.search(line)
        clsName = result.group("clsName")
        return clsName

    @staticmethod
    def tokenize(delimiters, line):
        tokens = Helper.takeApartLine(delimiters, line)
        return tokens

    @staticmethod
    def ftokenize(delimiters, file_):
        sum = []
        with open(file_, "r") as f:
            for line in f:
                r = Parser.tokenize(delimiters, line)
                sum.extend(r)
        return sum

    def is_finished(self):
        return self.curr == self.token_size-1

    def next_token(self):
        if self.curr != self.token_size - 1:
            return self.tokens[self.curr+1]
        return None

    def find(self, item, find_flag=FIND_EQUAL):
        if not self.tokens:
            return -1
        while 1:
            if self.curr >= self.token_size:
                return -1
            if not self.is_finished():
                if find_flag == Parser.FIND_EQUAL:
                    if self.tokens[self.curr] == item:
                        return self.curr
                if find_flag == Parser.FIND_STARTSWITH:
                    if self.tokens[self.curr].startswith(item):
                        return self.curr
            self.curr += 1
        return -1

    def find_case(self):
        return self.find("case")

    def find_factory(self):
        return self.find("AttributeFactory.make", Parser.FIND_STARTSWITH)

    def find_left_parenthesis(self):
        return self.find("(")

    def find_right_parenthesis(self):
        return self.find(")")

    def find_comma(self):
        return self.find(",")

    def is_lelf_pthss(self):
        return self.tokens[self.curr] == "("

    def is_right_pthss(self):
        return self.tokens[self.curr] == ")"

    def is_left_brace(self):
        return self.tokens[self.curr] == "{"

    def is_right_brace(self):
        return self.tokens[self.curr] == "}"

    def is_comma(self):
        return self.tokens[self.curr] == ","

    def find_args(self):
        done = False
        args = []
        include_comma = False
        # move the parsing position
        self.curr += 1
        oneArg = []
        parenthese_stack = []
        brace_stack = []
        while 1:
            while 1:
                # if still in braces, include comma
                if parenthese_stack or brace_stack:
                    include_comma = True
                # if in no braces, end when comma is met
                if not parenthese_stack and not brace_stack:
                    include_comma = False
                if self.is_lelf_pthss():
                    parenthese_stack.append("(")
                    include_comma = True
                if self.is_right_pthss():
                    # if par..stack is empty but met a )
                    # that is the end of args
                    if not parenthese_stack: # if empty
                        done = True
                        break
                    else:
                        parenthese_stack.pop()
                if self.is_left_brace():
                    brace_stack.append("{")
                    include_comma = True
                if self.is_right_brace():
                    brace_stack.pop()
                # cut one arg off
                if include_comma == False:
                    # check if comma is met
                    if self.is_comma():
                        break
                token = self.tokens[self.curr]
                if token:
                    oneArg.append(token)
                self.curr += 1
            # meet "," or ")" outside parenthese, skip it
            self.curr += 1
            continuous = "".join(oneArg)
            if continuous:
                args.append(continuous)
            oneArg = [] # clear
            if done:
                break
        return args

    def find_break(self):
        return self.find("break")

    def find_method(self):
        pass

    def get_class_name(self):
        return self.tokens[self.curr].replace("Effect.Filter.k", "")

    def read(self, _file, delimiters=[]):
        if not delimiters:
            delimiters = Parser.delimiters
        self.tokens = Parser.ftokenize(delimiters, _file)
        self.token_size = len(self.tokens)
        self.curr = 0

def java2Json(fn):
    functionBegin = "public static Attribute makeFilterAttrsByType"
    temp = "temp.java"
    with open(fn, "r") as inF, open(temp, "w") as outF:
        do_copy = False
        for line in inF:
            if functionBegin in line:
                do_copy = True
            if do_copy:
                outF.write(line)


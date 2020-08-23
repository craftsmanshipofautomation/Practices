from lib.parser import Parser

class RWParser0(Parser):
    def find_render(self):
        return self.find("Effect.Filter.k", Parser.FIND_STARTSWITH)

    @staticmethod
    def prettify(args):
        ret = []
        for arg in args:
            if arg.startswith("PathTool.getFilterDir(context)+"):
                arg = arg.replace("PathTool.getFilterDir(context)+", "")
                arg = arg.replace('"', "")
                arg = arg.replace("/", "")
            ret.append(arg)
        return ret

    def parse(self, file_, delimiters=[]):
        """
        return a dictionary
        """
        if not delimiters:
            delimiters = Parser.delimiters
        self.tokens = Parser.ftokenize(delimiters, file_)
        self.token_size = len(self.tokens)
        self.curr = 0
        json = {}
        """
        [(a, [...]), (b, [...])]
        """
        while 1:
            found = self.find_case()
            if found == -1:
                break
            assert(self.find_render() != 1)
            class_name = self.get_class_name()
            self.find_left_parenthesis()
            args = self.find_args()
            args = RWParser0.prettify(args)
            #print (class_name, args)
            #json.append((class_name, args))
            json[class_name] = args
            self.find_break()
        return json

class JavaParser(Parser):
    def find_class_method_name(self):
        pass

    def find_class(self):
        while self.curr < self.token_size:
            self.find("class")
            if self.tokens[self.curr-1] == "public":
                return True
        return False

    def find_attrs(self):
        while self.curr < self.token_size:
            self.find("attrs.", Parser.FIND_STARTSWITH)
            if "put" in self.tokens[self.curr]:
                return True
        return False

    def find_type(self):
        """
        use after find_attrs
        """
        putx = self.tokens[self.curr]
        if putx:
            return putx.replace("attrs.put", "")
        return None

    def find_make(self):
        self.find("make", Parser.FIND_STARTSWITH)
        return self.tokens[self.curr].replace("make","")

    def find_keys(self):
        """
        name: type
        """
        ret = []
        filter = self.find_make().replace("Attrs", "Render")
        while 1:
            self.find_attrs()
            type = self.find_type()
            self.find_left_parenthesis()
            name = self.next_token().replace('"', "")
            if name != "type":
                ret.append((name, type))
            self.find(";")
            may_be_return = self.next_token()
            if may_be_return == "return":
                break
        return (filter, ret)

    def parse(self, delimiters=[]):
        ret = []
        self.find_class()
        while 1:
            r = self.find_keys()
            ret.append(r)
            if self.find_make() == "FilterAttrsByType":
                break
        return ret



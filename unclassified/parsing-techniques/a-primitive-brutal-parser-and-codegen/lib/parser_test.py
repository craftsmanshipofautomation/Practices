from parser import initClassMap, \
                    Parser,\
                    Helper

import unittest


class TestGenerator(unittest.TestCase):
    def setUp(self):
        self.GClassMap = {}
    def test_initClassMap(self):
        self.GClassMap = initClassMap(r"../basic-data/all-filters.data")
        self.assertEqual(self.GClassMap["NoneFilterRender"], "default")
        self.assertEqual(self.GClassMap["IF1977FilterRender"], "1977")
        self.assertEqual(self.GClassMap["IFNashvilleFilterRender"], "Nashville")
        self.assertEqual(self.GClassMap["IFWaldenFilterRender"], "Walden")
        self.assertEqual(self.GClassMap["HighlightShadowFilterRender"], "HighlightShadow")
        self.assertEqual(self.GClassMap["SketchFilterRender"], "Sketch")

    def test_Parser_getClassName(self):
        clsN1 = Parser.getClassName("case Effect.Filter.kIFBrannanFilterRender:")
        clsN2 = Parser.getClassName("case Effect.Filter.kSmoothToonFilterRender:  ")
        self.assertEqual(clsN1, "IFBrannanFilterRender")
        self.assertEqual(clsN2, "SmoothToonFilterRender")

    def test_Helper_splitByWhitespace(self):
        line = """     10 20        3000 40
        5000
        60
                70           
        8000       """
        res = Helper.splitByWhitespace(line)
        self.assertEqual(res[0], "10")
        self.assertEqual(res[1], "20")
        self.assertEqual(res[2], "3000")
        self.assertEqual(res[3], "40")
        self.assertEqual(res[4], "5000")
        self.assertEqual(res[5], "60")
        self.assertEqual(res[6], "70")
        self.assertEqual(res[7], "8000")

    def test_Helper_split(self):
        spliter = ["=", ":", ".*?"]
        word = "::==10=200.*?:3000.*?40000:5=6:7=:"
        res = Helper.split(spliter, word)
        self.assertEqual(res, ['10', '200', '3000', '40000', '5', '6', '7'])

    def rtest_Parser_tokenize(self):
        line = "case Effect.Filter.kFalseColorFilterRender:"
        res = Parser.tokenize(Parser.delimiters, line)
        self.assertEqual(res, ['case', 'Effect.Filter.kFalseColorFilterRender', ':'])
        line2 = ":a:b:c:d:"
        ds = [":"]
        r = Parser.tokenize(ds, line2)
        self.assertEqual(r, [":", "a", ":", "b", ":", "c", ":", "d", ":"])

    def test_Helper_takeApartWord(self):
        word = "1.0f))"
        de = ")"
        res = Helper.takeApartWord(de, word)
        self.assertEqual(res, ['1.0f', ')', ')'])
        word = "1.0f"
        de = ")"
        res = Helper.takeApartWord(de, word)
        self.assertEqual(res, ["1.0f"])
        word = "("
        de = "("
        res = Helper.takeApartWord(de, word)
        self.assertEqual(res, ["("])
        word = "(1.0f"
        de = "("
        res = Helper.takeApartWord(de, word)
        self.assertEqual(res, ["(", "1.0f"])

    def test_Parser_tokenize2(self):
        line = "new Color4F(1.0f, 0.0f, 1.0f, 1.0f))"
        res = Parser.tokenize(Parser.delimiters, line)
        #print res
        self.assertEqual(res, ['new', 'Color4F', '(', '1.0f', ',', '0.0f', ',', '1.0f', ',', '1.0f', ')', ')'])

    def fuck(self,whatever):
        #print(whatever)
        pass

    def rtest_Parser_ftokenize(self):
        res = Parser.ftokenize(Parser.delimiters, "../temp.java")
        self.fuck(res)

    def rtest_Parser_find_case(self):
        p = Parser()
        p.tokens = ["1", "2", "case", "3"]
        p.curr = 0
        p.token_size = 4
        r = p.find_case()
        self.assertEqual(2, r)

    def rtest_Parser_find_args(self):
        p = Parser()
        p.tokens = ["PathTool.getFilterDir", "(", "context", ")",  "+", "\"/nmap.png\"", ")"]
        p.curr = -1
        p.token_size = len(p.tokens)
        r = p.find_args()
        self.assertEqual(['PathTool.getFilterDir(context)+"/nmap.png"'], r)

    def rtest_Parser_find_args2(self):
        p = Parser()
        p.tokens = ["new", "Color4F", "(" , "1.0f", ",",  "0.0f", ",", "1.0f", ",", "1.0f", ")", ")"]
        foo = "".join(p.tokens)
        self.assertEqual(foo, "newColor4F(1.0f,0.0f,1.0f,1.0f))")

        p.curr = -1
        p.token_size = len(p.tokens)
        r = p.find_args()
        self.assertEqual(['newColor4F(1.0f,0.0f,1.0f,1.0f)'], r)

    def test_Parser(self):
        p = Parser()
        r = p.parse("../temp.java")
        print r


if __name__ == "__main__":
    unittest.main()

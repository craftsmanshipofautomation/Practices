from rwparser import RWParser0, JavaParser

import unittest

class TestGenerator(unittest.TestCase):
    def setUp(self):
        self.p = JavaParser()
        self.p.read("./source_code.data")
    
    def reset(self):
        self.p.curr = 0

    def test_Parser(self):
        p = RWParser0()
        r = p.parse("./source_code.data")
        print r

    def test_Parser_find_class(self):
        p = JavaParser()
        p.read("./source_code.data")
        p.find_class()
        self.assertEqual(p.tokens[p.curr-1], "public")
        self.assertEqual(p.tokens[p.curr], "class")
        self.assertEqual(p.tokens[p.curr+1], "AttributeFactory")

    def test_Parser_find_type(self):
        p = JavaParser()
        p.read("./source_code.data")
        p.find_class()
        p.find_attrs()
        t = p.find_type()
        self.assertEqual(t, "Int")

    def test_Parser_find_key(self):
        self.reset()
        self.p.find_class()
        t = self.p.find_keys()
        #print t

    def test_Parser_parse(self):
        self.reset()
        r = self.p.parse()
        for i in r:
            print i



if __name__ == "__main__":
    unittest.main()
import unittest

from lib.parser import Parser
from generator import HandlerA, Generator


class TestGenerator(unittest.TestCase):
    #print json.dumps({'4': 5, '6': 7}, sort_keys=True, indent=4, separators=(',', ': '))
    def rtest_HandlerA_jsonDump(self):
        HandlerA.jsonDump("temp.java")

    def rtest_HandlerA_is_number(self):
        n1 = "1.0f"
        n2 = "0.0f"
        n3 = "0.03"
        n4 = "3"
        self.assertEqual(HandlerA.is_number(n1), True)
        self.assertEqual(HandlerA.is_number(n2), True)
        self.assertEqual(HandlerA.is_number(n3), True)
        self.assertEqual(HandlerA.is_number(n4), True)

    def rtest_fill_template_variable(self):
        line = "sdfaf {{ ab }}...sdfasf {{c_d   }}"
        d = {"ab": "AB", "c_d": "CD"}
        r = Generator.fill_template_variable(line, d)
        self.assertEqual(r, "sdfaf AB...sdfasf CD")
    
    def rtest_generate(self):
        g = Generator()
        g.setup_env(output_dir="/home/root_/filter_test")
        g.generate()

    def test_create_make(self):
        g = Generator()
        output_dir="/home/root_/Pictures/crap"
        g.setup_env(output_dir)
        g.create_make()

if __name__ == "__main__":
    unittest.main()

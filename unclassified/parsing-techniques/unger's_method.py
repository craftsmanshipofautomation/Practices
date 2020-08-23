import sys
import copy
from time import gmtime, strftime
from datetime import datetime

def now():
    return str(datetime.now())
Rules = {
    "E" : ["E+E", "T"],
    "T" : ["T*T", "F"],
    "F" : ["(E)", "a", "b", "c"]
}

R_1 = {
    "E" : ["F+F", "F"],
    "F" : ["i"]
}
N_1 = ["E", "T", "F"]
#T_1 = ["i", "*", "+", "(", ")"]
T_1 = ["a", "b", "c", "*", "+", "(", ")"]
S_1 = "E"

class Grammar(object):
    def __init__(self, n, t, r, s):
        self.N = n
        self.T = t
        self.R = r
        self.S = s


def combine(lst, n, collect, R):
    l = len(lst)
    head = l - n
    if n == 1:
        collect.append(lst)
        ##print collect
        R.append(collect)
    else:
        for i in range(0, head+1):
            save = copy.deepcopy(collect)
            save.append(lst[:i+1])
            combine(lst[i+1:], n-1, save, R)


def enumerate_unger_string(string, n):
    if n > len(string):
        return list(string)
    R = []
    collect = []
    combine(string, n, collect, R)
    return R

def enumerate_unger_list(lst, n):
    if n > len(lst):
        return list(lst)
    R = []
    collect = []
    combine(lst, n, collect, R)
    R_2 = []
    for l in R:
        l_2 = []
        for e in l:
            l_2.append("".join(e))
        R_2.append(l_2)
    return R_2


def tear_apart_nonterm_and_term(grammar, pattern):
    """
    return:
    None if no terminal
    [i, j, k...] as i j k is the indexes of terminals
    """
    terms = []
    nonterms = []
    for i in xrange(len(pattern)):
        if pattern[i] in grammar.T:
            terms.append(i)
        if pattern[i] in grammar.N:
            nonterms.append(i)
    return terms, nonterms

def is_pattern_fit(grammar, pattern, token_list):
    tis, nis = tear_apart_nonterm_and_term(grammar, pattern)
    hit = 0
    for i in tis:
        if token_list[i] == pattern[i]:
            hit += 1
            token_list.pop(i)
    if hit > 0:
        return True
    return False

D = []

START = "START"
END = "END"

def classification_on_rhs(grammar, lst):
    non = []
    ter = []
    for e in lst:
        if e in grammar.T:
            ter.append(e)
        else:
            non.append(e)
    return ter, non

def split_rhs(grammar, rhs):
    splited = []
    type = []
    length = 1
    i = 0
    while i < len(rhs):
        j = i
        while j <= len(rhs):
            sub = rhs[i:j]
            if sub in grammar.N:
                splited.append(sub)
                type.append("N")
                i = j
                break
            if sub in grammar.T:
                splited.append(sub)
                type.append("T")
                i = j
                break
            else:
                j += 1
    for i in xrange(1, len(splited)):
        if type[i] != type[i-1]:
            length += 1
    if length == 1:
        length = len(splited)
    tis = [i for i in xrange(len(type)) if type[i] == "T"]
    nis = [i for i in xrange(len(type)) if type[i] == "N"]

    return splited, length, tis, nis

def is_matched(grammar, input_, start_symbol, collect):
    print "-->[entrance] dealing '{}' with start symbol '{}'".format(input_, start_symbol)
    #collect.append((input_, start_symbol))
    print "----[**********] Path = {}".format(collect)
    RHSs = grammar.R[start_symbol]
    terms, nonterms = classification_on_rhs(grammar, RHSs)
    print "----terminals = {}".format(terms)
    print "----non-terminals = {}".format(nonterms)
    #check if it is should end now
    for t in terms:
        if t == input_:
            print "----------[1] Derivation {}' => '{}' in 1 step, branch ends".format(start_symbol, input_)
            return True
    print "----------From '{}' there is no derivation to '{}' in 1 step".format(start_symbol, input_)
    #nonterms = [start_symbol]
    # or it need further derivation
    print "----------rhs of rule", nonterms
    #compare right hand side of rule with sentence
    # eg: compare a/b with E+E will fail becuz / does not match +
    # a/b will possibly match T becuz, T's tis is None
    match = []
    for non_term_on_rule_rhs in nonterms:
        splited_rhs, length, tis, nis = split_rhs(grammar, non_term_on_rule_rhs)
        print "!!!!!!!!!!!!!!", splited_rhs, length, tis, nis
        possibilities = enumerate_unger_string(input_, length)
        if len(input_) < length:
            print "sentence {} too small for rhs {}".format(input_, non_term_on_rule_rhs)
            continue
        #tis, nis = tear_apart_nonterm_and_term(grammar, splited_rhs)
        for token_list in possibilities:
            print "======================", token_list
            error = 0
            #if there is terminals
            if tis:
                for i in tis:
                    if not token_list[i] == splited_rhs[i]:
                        error += 1
                if error > 0:
                        #print "'{}' does not matches rule '{}' -> '{}': ".format(token_list, start_symbol, non_term_on_rule_rhs)
                        pass
                else:
                    print "----------Partition {} matches rule '{}' -> '{}': ".format(token_list, start_symbol, non_term_on_rule_rhs)
                    #(sentence, rhs of rule, tis, nis)
                    match.append((token_list, non_term_on_rule_rhs, tis, nis))
            else:
                # no terminals, nontermial might be adjacent with neighbors directly
                adj_perts = enumerate_unger_list(splited_rhs, length)
                nis_2 = [i for i in xrange(length)]
                for p in adj_perts:
                    print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", p, nis_2
                    match.append((token_list, p, [], nis_2))



    deadend_error = 0
    if not match:
        # there is no further derivation available, as the simpliest RHS(one character) fail to match the sentence
        for nonterm in nonterms:
            print "----------[dead] 'the last step of derivation meets a dead end: {lfs}' -> '{rhs}', but '{sentence}' as a '{lfs}' does not match '{rhs}'".format(lfs=start_symbol, rhs=nonterm, sentence=input_)
            deadend_error += 1
    if deadend_error > 0:
        return False

    for m in match:
        sentence = m[0]
        non_term_on_rule_rhs = m[1]
        print "*********************", sentence, non_term_on_rule_rhs, tis, nis
        tis = m[2]
        nis = m[3]
        if len(nis) == 1:
            print "------------[single part] matching '{}' with non_term_on_rule_rhs '{}' index '{}': ".format(sentence[0], non_term_on_rule_rhs[nis[0]], nis)
            # expansion of start_symbol
            collect.append((input_, non_term_on_rule_rhs))
            new = []
            ret = is_matched(grammar, sentence[0], non_term_on_rule_rhs[nis[0]], new)
            if ret:
                collect.extend(new)
                return True
            else:
                collect.pop()
                continue
        else:
            false = 0
            news = []
            # expansion of start_symbol
            collect.append((input_, "".join(non_term_on_rule_rhs)))
            for n in nis:
                dup = [(sentence[n], non_term_on_rule_rhs[n])]
                ret = is_matched(grammar, sentence[n], non_term_on_rule_rhs[n], dup)
                if not ret:
                    false += 1
                else:
                    news.append(dup)
            if false == 0:
                print "------------[multi-part] matching '{}' with non_term_on_rule_rhs '{}' index '{}': ".format(sentence, non_term_on_rule_rhs, nis)
                for new in news:
                    collect.extend(new)
                return True
            else:
                collect.pop()
                continue
    return False


def match_derivation(G, sentence, start_symbol):
    collect = [(sentence, start_symbol, START)]
    if not is_matched(G, input_, start_symbol, collect):
        collect.append("FAILED")
    print collect

if __name__ == "__main__":
    start_symbol = sys.argv[2]
    input_ = sys.argv[1]
    N_2 = ["S", "A", "B", "C"]
    T_2 = ["a", "b"]
    R_2 = {
        "S": ["AB", "BC"],
        "A": ["BA", "a"],
        "B": ["CC", "b"],
        "C": ["AB", "a"]
    }
    G = Grammar(N_2, T_2, R_2, "S")
    #G = Grammar(N_1, T_1, Rules, "E")
    match_derivation(G, input_, start_symbol)

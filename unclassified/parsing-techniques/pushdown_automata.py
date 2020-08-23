R = {
    ("a", "S"):"B",
    ("b", "S"): "A",
    ("a", "A"): "e",
    ("b", "A"): "AA",
    ("b", "B"): "e",
    ("a", "B"): "BB"

}

def push(stack, string):
    for i in string:
        stack.append(i)

def match(inp, stack_top_alph, rules):
    if (inp, stack_top_alph) in rules:
        return rules[(inp, stack_top_alph)]
    else:
        return None

def pushdown(input, start_symbol):
    stack = []
    push(stack, start_symbol)
    for i in input:
        stktop = stack[-1]
        placement = match(i, stktop, R)
        if not placement:
            print "{} does not match {} on the stack, transition failed".format(i, stktop)
            return False
        print "{} matches {} on the stack, transition suceed".format(i, stktop)
        stack.pop()
        if placement != "e":
            push(stack, placement)
        print "stack is now :{}".format(stack)
    if not stack:
        print "input {} is accepted!"
        return True
    return False
        
    




if __name__ == "__main__":
    import sys
    input = sys.argv[1]
    pushdown(input, "S")

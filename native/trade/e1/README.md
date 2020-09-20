## Matrix multiplication

Please implement the mutiplication of two matrices for the following two cases
1. each element in the matrix is a complex number(a + bi)
2. each element in the matrix is a triple(a0, a1, a2), the addition and multiplication betweentwo triples are defined as follows:
`a0, a1, a2) + (b0, b1, b2) = (a0 + b0, a1 + b1, a2 + b2)`
`(a0, a1, a2) * (b0, b1, b2) = (a0 * b0, a1 * b1, a2 * b2)`

You need to design the data structures(complex, triple, matrix, etc) on your own. Use float asthe basic data type in this question.

## Arithmetic expression parsing

Please implement an arithmetic expression parser that can evaluate strings like `((1+sin(0))*(3.0+(4*5)))` to `23.0`

Assumptions:

1. every binary operation a+b in the input expression are wrapped in a pair of parentheses(a+b).

Requirements:
1. support the following operations: ` + - * / sin cos`

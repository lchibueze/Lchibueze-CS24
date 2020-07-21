# Convert

_Due Monday, July 27th, before midnight Pacific Time._

In this assignment you'll be dealing with expressions (again), but this time the
goal isn't to solve them.  Now you want to convert them  into different formats.
You'll write  a program  that can  read expressions  in either prefix or postfix
notation and then output them in any notation.

The completed program will run like this:

```
[wendy@neverland convert]$ ./convert prefix infix
1.2.3.4
Invalid token: 1.2.3.4
+ 3 4
=> 3 + 4
  - 5 - -7 9
=> 5 - (-7 - 9)
```


## Your Assignment

- Implement an expression converter.
- You can use anything from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.


## The Program

Your program  should take  two arguments  on the command line.  The first is the
name of an input format, and the second is the name of an output format.  If you
don't receive exactly two arguments, or if either argument isn't a valid format,
print the following usage message and exit:

```
USAGE: convert [input-format] [output-format]
  Valid input formats:   prefix, postfix
  Valid output formats:  prefix, infix, postfix
```

If the command line arguments are valid,  your program should read from standard
input one line at a time.  Each line will be an expression  in the input format;
parse it into an  **abstract syntax tree** (AST).  Then convert it to the output
format and  print the result.  When you reach the end  of the input stream, your
program should exit.


## Input Formats

Each line of input will consist of a series of **tokens**.  Tokens are separated
by whitespace.  An input line may have leading or trailing spaces,  and may have
multiple spaces between  tokens.  Read each line  according to the input  format
specified on the command line:

- If the input format is `prefix` then parse each line as a prefix expression
  (also known as Polish Notation).  The easiest way to do this is to use
  recursion.

- If the input format is `postfix` then parse each line as a postfix expression
  (also known as Reverse Polish Notation).  The easiest way to do this is to use
  a loop and a stack.

There may be errors in your input stream.  If you encounter an error,  print the
correct error message as listed below, then move on to the next line of input.

- If you encounter an invalid token, print `Invalid token: XXX` (where `XXX` is
  the token you couldn't parse).

- If any operator doesn't have enough operands, or if there are no tokens in the
  input, print `Not enough operands.`.

- If there are too many operands for a single expression or extra tokens at the
  end of the expression, print `Too many operands.`.

Parsing should be done by the AST parsing functions in `AST.cpp`.  If parsing is
successful, these functions should return a  pointer to the root node of a newly
created abstract syntax tree.


## Output Formats

Each  line of output should follow  the same formatting rules as the input,  but
with stricter whitespace rules: tokens should be separated by exactly one space,
and lines should not have any leading  or trailing  whitespace.  Print each line
according to the output format specified on the command line:

- If the output format is `prefix` then print the expression in Polish Notation.

- If the output format is `postfix` then print the expression in Reverse Polish
  Notation.

- If the output format is `infix`  then print the expression in the  usual human
  infix notation. Add as few parentheses as are necessary to guarantee that your
  infix expression has  the same structure as your AST.  See the Operators table
  in the Reference section for order of operations rules.

  ```
  [wendy@neverland convert]$ ./convert postfix infix
  1 2 + 3 +
  => 1 + 2 + 3
  4 5 6 + +
  => 4 + (5 + 6)
  7 8 9 * +
  => 7 + 8 * 9
  108 ~
  => ~ 108
  ```

Formatting should be done by  the AST member functions  named after each  output
format. When printing expressions, prefix them with `=> ` for readability. There
are no error cases.  If you were able to parse an expression as a valid AST then
you can render it in any format.


## Reference

### Numbers

All numbers are `double`s.  Numbers in the input will always be in this format:

- Optionally: A `+` or `-` indiciating the sign.
- One or more decimal digits (`0` through `9`).
- Optionally: A `.` followed by one or more decimal digits.

Convert numbers to strings using a `std::stringstream`. This may produce strings
in scientific notation;  you don't need to be able to parse these, but it's also
not a problem if you can (such inputs won't be tested).


### Operators

All operators are listed below (numbers are included for completeness):

| Symbol | Operation       | Arity | Associativity | Precedence |
|--------|-----------------|-------|---------------|------------|
| `+`    | Addition        | 2     | Left          | Lowest     |
| `-`    | Subtraction     | 2     | Left          | Lowest     |
| `*`    | Multiplication  | 2     | Left          | Low        |
| `/`    | Division        | 2     | Left          | Low        |
| `%`    | Remainder       | 2     | Left          | Low        |
| `~`    | Negation        | 1     | Right*        | Medium     |
| `^`    | Exponentiation  | 2     | Right         | High       |
| Number | Literal Value   | 0     | None          | Highest    |

Note that the values in the Associativity and Precedence columns only make sense
when working with infix notation. In the other notations, order of operations is
determined by the order of the tokens in the input stream.


## Hints

- Use `while(std::getline(...))` to loop over lines of input.
- Using `std::stod()` or a `std::stringstream` is a good way to parse tokens as
  `doubles` - but be aware that these will only consume half of an invalid token
  like `72xy`.
- Beware of memory leaks.  Make sure your parsing functions clean up any AST
  nodes they've created if you encounter a parse error.

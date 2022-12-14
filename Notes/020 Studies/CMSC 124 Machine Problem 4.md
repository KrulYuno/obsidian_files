
CMSC 124 Machine Problem 4
**Topic Coverage**: Expressions

---

Install [rust](https://doc.rust-lang.org/book/ch01-01-installation.html) or use [Rust Playground](https://play.rust-lang.org/) on your web browser.

---

## 1. Create a program that will accept an expression in infix notation and is capable of converting it to prefix as well as postfix notation. Similarly, you should also be able to accept an expression in prefix notation and convert it to infix and postfix notation; and accept an expression in postfix notation, and convert it to infix and prefix notation. Assumelikewise that an expression can be erroneous, thus provide appropriate error-handling schemes.

| **Input** | **postfix**                    | 
| --------- | ----------------------------- |
| Infix     | Prefix and postfix equivalent |
| Prefix    | Infix and postfix equivalent  |
| Postfix   | Infix and prefix equivalent   |
^Ypn5Cf

Sample expressions:

| Infix                            | Prefix           | Postfix            |
| -------------------------------- | ---------------- | ------------------ |
| A+B\*C+D                         | ++A\*BCD         | ABC\*+D+           |
| (A+B)\*(C+D)                     | \*+AB+CD         | AB+CD+\*           |
| A\*B+C\*D                        | +\*AB\*CD        | AB\*CD\*+          |
| A+B+C+D                          | +++ABCD          | AB+C+D+            |
| (A+B)\*C                         | \*+ABC           | AB+C\*             |
| A\*B+C/D                         | +\*AB/CD         | AB\*CD/+           |
| A\*(B+C)/D                       | /\*A+BCD         | ABC+\*D/           |
| a\*(b+c/d)                       | \*a+b/cd         | abcd/+\*           |
| a\*(b+c)                         | \*a+bc           | abc+\*             |
| a/b+c/d                          | +/ab/cd          | ab/cd/+            |
| ((a+b)\*c)-d                     | -\*+abcd         | ab+c\*d-           |
| (a+(((b\*c)-((d/(e^f))\*g))\*h)) | +a\*-\*bc\*/d^efgh | abc\*def^/g\*-h\*+ |
^5aqOWm

Source Code: 
- https://github.com/KrulYuno/obsidian_files/blob/master/Codes/mp4_expression_notation_converter.rs 
- https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=be1166c26d86ad5e2a133c84a021130a 
- https://replit.com/@KrulYuno/CMSC124-Machine-Problem-41#src/main.rs


<div style="page-break-after: always;"></div>

## 2. Use the same algorithms you have implemented in #1 to accept an expression (this time variables are actual numbers) and evaluate them to give the final answer. For clarity purposes, separate each token with a space. Also, assume that user may input erroneous expressions, so include exception handling in your implementation. Shown below are some example runs:
Expression: 6 2 3 + - 3 8 2 / + * 2 ^ 3 +
Answer: 52

Expression: + 9 * 2 6
Answer: 21

Expression: - + 7 * 4 5 + 2 0
Answer: 25

Expression: - + 8 / 6 3 2
Answer: 8

Expression: ( 5 + 10 ) / ( 20 / 4 )
Answer: 3

Source Code: 
- https://github.com/KrulYuno/obsidian_files/blob/master/Codes/mp4_expression_notation_evaluator.py
- https://replit.com/@KrulYuno/CMSC124-Machine-Problem-42#main.py

---

## Solution to problem 1:
Stack will be used to implement the conversion process.

**Converting Infix expression to Postfix expression**:
1. Create a stack `op_stack` for operators and an postfix list `postfix`.
2. .Create a precedence rank for the operators:
	1. `^` (highest)
	2. `*` and `/`
	3. `+` and `-`
	4. `(` (lowest)
3. Loop each tokens of the infix expression. Notice that each tokens only contains one character.
	1. If the character token is an *operand*, append to `postfix` (e.g. A or B)
	2. If the character token is a left parenthesis, push to `op_stack`.
	3. If the character token is a right parenthesis, pop every items in the `op_stack` until the corresponding left parenthesis is popped. Append each operator to `postfix`.
	4. If the character token is an *operator* (e.g. + or \*), remove existing then append to `postfix` the higher or equal precedence operators in the `op_stack` and then push the operator to the `op_stack`.
4. Once all tokens are processed, pop all tokens in `op_stack` and append it to `postfix`. 
```rust
fn infix_to_postfix(expression: &str) -> Vec<char> {
    let mut op_stack: Vec<char> = Vec::new();
    let mut postfix: Vec<char> = Vec::new();
    for token in expression.chars() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                postfix.push(token);
            }
            '(' => {
                op_stack.push(token);
            }
            ')' => {
                let mut top_token: Option<char> = op_stack.pop();
                while top_token != Some('(') {
                    postfix.push(top_token.unwrap());
                    top_token = op_stack.pop();
                }
            }
             '+' | '-' | '*' | '/' | '^' => {
                while !op_stack.is_empty()
                    && precedence_rank(op_stack.last()) >= precedence_rank(Some(&token))
                {
                    postfix.push(op_stack.pop().unwrap());
                }
                op_stack.push(token);
            }
            _ => {}
        }
    }
    while !op_stack.is_empty() {
        postfix.push(op_stack.pop().unwrap());
    }
    postfix
}
```
`infix_to_postfix()` function takes input as string and iterates each characters as a token from left to right. This function returns a vector of characters.

**Converting Infix expression to Prefix expression**:
Stack is used to convert the expression.

The same method is implemented in converting infix to prefix from infix to postfix, except iteration is reversed.
```rust
fn infix_to_prefix(expression: &str) -> Vec<char> {
    let mut op_stack: Vec<char> = Vec::new();
    let mut prefix: Vec<char> = Vec::new();
    for token in expression.chars().rev() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                prefix.push(token);
            }
            ')' => {
                op_stack.push(token);
            }
            '(' => {
                let mut top_token: Option<char> = op_stack.pop();
                while top_token != Some(')') {
                    prefix.push(top_token.unwrap());
                    top_token = op_stack.pop();
                }
            }
            '+' | '-' | '*' | '/' | '^' => {
                while !op_stack.is_empty()
                    && precedence_rank(op_stack.last()) > precedence_rank(Some(&token))
                {
                    prefix.push(op_stack.pop().unwrap());
                }
                op_stack.push(token);
            }
            _ => {}
        }
    }
    while !op_stack.is_empty() {
        prefix.push(op_stack.pop().unwrap());
    }
    prefix.reverse();
    prefix
}
```
Notice that the iteration starts from the end of the index `for token in expression.chars().rev()` and the checks for the parenthesis have switched.

**Converting Postfix expression to Infix expression***
Stacks is implemented for the conversion.

1. Create stack `stack` for storing the operands.
2. Iterate through the expression, token by token.
3. If token is an operand, push it to `stack`
4. If token is an operator, pop the `stack` two times
	1. First pop, set it as the right operand `operand_right`
	2. Second pop, set it as the left operand `operand_left`
5. Push: ( `operand_left` token `operand_right` )
```rust
fn postfix_to_infix(expression: &str) -> String {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars() {
        match token {
            'A'..='Z' | 'a'..='z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
			    let operand_right: String = stack.pop().unwrap();
                let operand_left: String = stack.pop().unwrap();

                let mut temp_string: String = String::new();
                temp_string.push('(');
                temp_string.push_str(&operand_left);
                temp_string.push(token);
                temp_string.push_str(&operand_right);
                temp_string.push(')');
                stack.push(temp_string.to_owned());
            }
            _ => {}
        }
    }
    stack[0].to_owned()
}
```
Unlike other functions, this returns a String instead of a character vector. I initiated the stack as a string so that it will be easier to pop concatenated tokens like `(a+b)`.

**Converting Postfix expression to Prefix expression***
Stacks is implemented for the conversion.

1. Create a stack `stack`.
2. Iterate the input expression from left to right as tokens.
3. Push to `stack` if token is an operand.
4. Pop `stack` twice if token is an operator.
	1. Set `operand_right` as the first pop.
	2. Set `operand_left` as the second pop.
5. Concatenate the token, `operand_left`, and `operand_right` (e.g. `+AB`)
6. Push the concatenated string.

```rust
fn postfix_to_prefix(expression: &str) -> String {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
                let operand_right: String = stack.pop().unwrap();
                let operand_left: String = stack.pop().unwrap();
                let mut temp_string: String = String::new();
                temp_string.push(token);
                temp_string.push_str(&operand_left);
                temp_string.push_str(&operand_right);
                stack.push(temp_string);
            }
            _ => {}
        }
    }
    stack[0].to_owned()
}
```
A bit similar to converting postfix to infix, but without the parentheses. Still returns a String.

**Converting Prefix expression to Infix expression***
Stacks is implemented for the conversion.

```rust
fn prefix_to_infix(expression: &str) -> String {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars().rev() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
                let operand_left: String = stack.pop().unwrap();
                let operand_right: String = stack.pop().unwrap();
                let mut temp_string: String = String::new();
                temp_string.push('(');
                temp_string.push_str(&operand_left);
                temp_string.push(token);
                temp_string.push_str(&operand_right);
                temp_string.push(')');
                stack.push(temp_string);
            }
            _ => {}
        }
    }
    stack[0].to_owned()
}
```


**Converting Prefix expression to Postfix  expression***
Stacks is implemented for the conversion.

```rust
fn prefix_to_postfix(expression: &str) -> String {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars().rev() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
                let operand_left: String = stack.pop().unwrap();
                let operand_right: String = stack.pop().unwrap();
                let mut temp_string: String = String::new();
                temp_string.push_str(&operand_left);
                temp_string.push_str(&operand_right);
                temp_string.push(token);
                stack.push(temp_string);
            }
            _ => {}
        }
    }
    stack[0].to_owned()
}
```

A helper method for returning the operator's precedence value.
```rust
fn precedence_rank(token: Option<&char>) -> u32 {
    match token {
        Some(&'(') => return 1,
        Some(&')') => return 1,
        Some(&'+') => return 2,
        Some(&'-') => return 2,
        Some(&'*') => return 3,
        Some(&'/') => return 3,
        Some(&'^') => return 4,
        _ => return 0,
    }
}
```

A helper method for returning concatenated string of vector characters..
```rust
fn result_to_string(result: Vec<char>) -> String {
    let mut expression: String = "".to_owned();
    for c in result {
        expression.push(c);
    }
    expression
}
```

Method for checking the type of the input expression.
```rust
fn check_notation_type(expression: &str) -> isize {
    match expression.chars().nth(0).unwrap() {
        '+' | '-' | '*' | '/' | '^' => {
            return -1;
        }
        _ => match expression.chars().nth_back(0).unwrap() {
            '+' | '-' | '*' | '/' | '^' => {
                return 1;
            }
            _ => return 0,
        },
    }
}
```
**Return values:**
-  `-1`, prefix
- `1`, postfix
- `0`, infix

**Next up is checking if the expression notations are valid:**
Stacks are still used to implement the algorithm. Returns a boolean value.

Method for checking if the Prefix Notation is valid. 
```rust
fn check_prefix(expression: &str) -> bool {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars().rev() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
                if stack.last() != None {
                    let operand_left: String = stack.pop().unwrap();
                    if stack.last() != None {
                        let operand_right: String = stack.pop().unwrap();
                        let mut temp_string: String = String::new();
                        temp_string.push_str(&operand_left);
                        temp_string.push_str(&operand_right);
                        temp_string.push(token);
                        stack.push(temp_string);
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            ' ' => {}
            _ => return false,
        }
    }
    if stack.len() != 1 {
        return false;
    }
    true
}
```
Nesting the if-else statements to ensure expression validation since it checks if the two operands exist and an operator exists. The last part checks if the length of the stack is `1`; If it is a valid expression, it should only return one item in the stack.

Same method it implemented from the Prefix checker for this Postfix notation validation.
```rust
fn check_postfix(expression: &str) -> bool {
    let mut stack: Vec<String> = Vec::new();
    for token in expression.chars() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                stack.push(token.to_string());
            }
            '+' | '-' | '*' | '/' | '^' => {
                if stack.last() != None {
                    let operand_right: String = stack.pop().unwrap();
                    if stack.last() != None {
                        let operand_left: String = stack.pop().unwrap();
                        let mut temp_string: String = String::new();
                        temp_string.push_str(&operand_left);
                        temp_string.push_str(&operand_right);
                        stack.push(temp_string);
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            ' ' => {}
            _ => return false,
        }
    }
    if stack.len() != 1 {
        return false;
    }
    true
}
```


```rust
fn check_infix(expression: &str) -> bool {
    let mut operand_stack: Vec<char> = Vec::new();
    let mut operator_stack: Vec<char> = Vec::new();
    for token in expression.chars() {
        match token {
            'a'..='z' | 'A'..='Z' => {
                operand_stack.push(token);
            }
            '+' | '-' | '*' | '/' | '^' => {
                if !operator_stack.is_empty() {
                    if precedence_rank(Some(&token)) >= precedence_rank(operator_stack.last()) {
                        operator_stack.push(token);
                    } else {
                        if operand_stack.last() != None {
                            operand_stack.pop();
                            if operand_stack.last() != None {
                                operand_stack.pop();
                                if operator_stack.last() != None {
                                    operator_stack.pop();
                                    operand_stack.push('X');
                                    operator_stack.push(token);
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    }
                } else {
                    operator_stack.push(token);
                }
            }
            '(' => {
                operator_stack.push(token);
            }
            ')' => {
                let mut top_token: Option<char> = operator_stack.pop();
                while top_token != Some('(') {
                    if operand_stack.last() != None {
                        operand_stack.pop();
                        if operand_stack.last() != None {
                            operand_stack.pop();
                            operand_stack.push('X');
                            top_token = operator_stack.pop();
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
            }
            ' ' => {}
            _ => return false,
        }
    }
    for _ in operator_stack {
        if operand_stack.last() != None {
            operand_stack.pop();
            if operand_stack.last() != None {
                operand_stack.pop();
                operand_stack.push('X');
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    if operand_stack.len() != 1 {
        return false;
    }
    true
}
```

Unit tests exists to check if the methods works as expected.


## Solution to number 2:

The same algorithm is used for evaluating the numbers from solution \#1.

Returns the precedence rank of the operators.
```python
def precedence_rank(token: str):
    match token:
        case '(':
            return 1
        case ')':
            return 1
        case '+':
            return 2
        case '-':
            return 2
        case '*':
            return 3
        case '/':
            return 3
        case '^':
            return 4
        case _:
            return 0
```

Converts a string into a number.
```python

def number_identifier(number:str):
    try:
        return int(number)
    except:
        return None
```

Returns the arithmetic calculation / evaluation of the input expression.
```python
def arithmetic_operations(operator, left, right):
    match operator:
        case '+':
            return left + right
        case '-':
            return left - right
        case '*':
            return left * right
        case '/':
            return left / right
        case '^':
            return left ** right
        case _:
            return None
```

Evaluates and checks if the expression is valid, returns the evaluated expression if valid for postfix notation.
```python
def evaluate_postfix(expression: str):
    tokens      = expression.split()
    stack       = list()
    
    for token in tokens:
        if number_identifier(token) == None:
            match token:
                case '+' | '-' | '*' | '/' | '^':
                    try:
                        operand_right   = stack.pop()
                        operand_left    = stack.pop()
                        value           = arithmetic_operations(token, operand_left, operand_right)
                        stack.append(value)
                    except:
                        print("Invalid Expression.")
                        return None
                    
                case _:
                    print("Invalid Expression.")
                    return None

        else:
            stack.append(number_identifier(token))
    
    if len(stack) != 1:
        print("Invalid Expression.")
        return None

    return stack[0]
```


Evaluates and checks if the expression is valid, returns the evaluated expression if valid for prefix notation.
```python
def evaluate_prefix(expression: str):
    tokens      = expression.split()
    stack       = list()

    tokens.reverse()
    for token in tokens:
        if number_identifier(token) == None:
            match token:
                case '+' | '-' | '*' | '/' | '^':
                    try:
                        operand_left    = stack.pop()
                        operand_right   = stack.pop()
                        value           = arithmetic_operations(token, operand_left, operand_right)
                        stack.append(value)
                    except:
                        print("Invalid Expression.")
                        return None

                case _:
                    print("Invalid Expression.")
                    return None

        else:
            stack.append(number_identifier(token))

    if len(stack) != 1:
        print("Invalid Expression.")
        return None

    return stack[0]
```

Converts an infix notation to postfix notation.
```python

def infix_to_postfix(expression: str):
    tokens          = expression.split()
    operator_stack  = list()
    postfix_stack   = list()

    for token in tokens:
        number_token    = number_identifier(token)
        if number_token == None:
            match token:
                case '+' | '-' | '*' | '/' | '^':
                    while len(operator_stack) > 0 \
                        and precedence_rank(operator_stack[-1]) >= precedence_rank(token):
                        try:
                            postfix_stack.append(operator_stack.pop())        
                        except:
                            print("Invalid Expression.")
                            return None
                    operator_stack.append(token)

                case '(':
                       operator_stack.append(token)

                case ')':
                    try:
                        top_token   = operator_stack.pop()
                        while top_token != '(': 
                            postfix_stack.append(top_token)
                            top_token   = operator_stack.pop()

                    except:
                        print("Invalid Expression.")
                        return None

                case _:
                    print("Invalid Expression.")
                    return None
        else:
            postfix_stack.append(number_token)

    while len(operator_stack) > 0:
        try:
            postfix_stack.append(operator_stack.pop())
        except:
            print("Invalid Expression.")
            return None

    return ' '.join(map(str, postfix_stack))
```

A helper function that checks the type of notation from the input expression.
```python
def check_notation_type(expression: str) -> int:
    if expression[0] in ['-', '+', '*', '/', '^']:
        return -1
    elif expression[-1] in ['-', '+', '*', '/', '^']: 
        return 1
    else:
        return 0
```


# References
---
- _2.9. Infix, Prefix and Postfix Expressions ??? Resolu????o de Problemas Usando Python_. (n.d.). https://panda.ime.usp.br/panda/static/pythonds_pt/02-EDBasicos/InfixPrefixandPostfixExpressions.html
- Expression Evaluation Using Stack. (n.d.). _Code Studio_. https://www.codingninjas.com/codestudio/library/expression-evaluation-using-stack
- https://www.web4college.com/converters/postfix-to-prefix-to-postfix.php
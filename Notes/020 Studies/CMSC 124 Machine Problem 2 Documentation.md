>[!INFO]
> Status: #DISCONTINUED 
> Tags: #CMSC124 #Machine_Problem

----
# Machine Problem 2
No need to make an interpreter for this MP, however I think that's much better?
More info on BNF [[Backus-Naur Form|here]].

```
Valid strings:
~x+~y
(x+z-y)
z-(x+y)

Invalid strings:
a+b
xy-xz
z(x+y)

-----------------

BNF:
	<expression> ::= <term> | ~<term> | <expression><operator><term>
	<term>       ::= <expression> | (<expression>) | <sign>
	<sign>       ::= <identifier> | ~<identifier>
	<operator>   ::= + | - 
    <identifier> ::= A | B | ... | Z | a | b | ... | z

```

```
Make a BNF for palindrome (without spaces)

Palindrome: pop, pop a pop, a but tuba  
Not a palindrome: hey, joe, the quick brown fox

BNF:
	<palindrome>  ::= AA | BB | CC | ... | ZZ |
				     aa | bb | cc | ... | zz |
				     00 | 11 | 22 | ... | 99 |
				     !! | @@ | ## | $$  | %% | ^^ | __ | {{ | }} | || | \\ | "" | << | ,, | ?? | \\ |
					 && | ** | (( | ))  | -- | ++ | == | [[ | ]] | :: | ;; | '' | >> | .. | // | ~~ | ``
					 A<palindrome>A | B<palindrome>B | C<palindrome>C | ... | Z<palindrome>Z |
				     a<palindrome>a | b<palindrome>b | c<palindrome>c | ... | z<palindrome>z |
				     !<palindrome>! | @<palindrome>@ | #<palindrome># | $<palindrome>$  | %<palindrome>% | 
				     ^<palindrome>^ | _<palindrome>_ | {<palindrome>{ | }<palindrome>}  | |<palindrome>| | 
				     \<palindrome>\ | "<palindrome>" | <<palindrome>< | ,<palindrome>,  | ?<palindrome>? | \<palindrome>\ |
					 &<palidrome>&  | *<palidrome>*  | (<palidrome>(  | )<palidrome>)   | -<palidrome>-  | 
					 +<palidrome>+  | =<palidrome>=  | [<palidrome>[  | ]<palidrome>]   | :<palidrome>:  | 
					 ;<palidrome>;  | '<palidrome>'  | ><palidrome>>  | .<palidrome>.   | /<palidrome>/  | 
					 ~<palidrome>~  | `<palidrome>`  |
					 <character> | 


	<character>  ::= A | B | ... | Z | 
					 a | b | ... | z |
					 0 | 1 | ... | 9 |
					 ! | @ | # | $ | % | ^ | _ | { | } | | | \ | " | < | , | ? | \ |
					 & | * | ( | ) | - | + | = | [ | ] | : | ; | ' | > | . | / | ~ | `
```
I think making a full character palindrome like with symbols and such is better... However, just implement alphanumeric characters for the machine problem.
For without spaces, just make it on the implementation part since this BNF does not ignore spaces.

# basic_bnf_op.py
This is our grammar:
```
BNF:
<expression> ::= <term> | ~<term> | <expression><operator><term>
<term> ::= <expression> | (<expression>) | <sign>
<sign> ::= <identifier> | ~<identifier>
<operator> ::= + | -
<identifier> ::= x | y | z
```
This code is hard coded to only work for the specific grammar above.

# bnf_palindrome.py

no documentation, i wont write it. too lazy.


[[CMSC 124 Machine Problem 2|Machine Problem 2]]

---
References:
- https://stackoverflow.com/questions/30961700/bnf-grammar-for-a-palindrome
 ```python
import re

def open_file(filename):
    with open(filename) as file:
        line_reader(file.readlines())

def line_reader(lines, includes = list()):
    for line in lines:
        sub_line = line.split(" ")
        if sub_line[0] == "#include":
            if sub_line[1] not in includes:
                includes.append(sub_line[1])
                i_file = re.findall("\w+[.]h", sub_line[1])
                open_file(i_file[0]) 
        else:
            print(line)

def main():
    filename = input()
    #filename = "inputFile2.cpp"
    open_file(filename)

if __name__ == "__main__":
   main() 
```

# aaiyaaa
i noticed something, removing `includes = list()` from the `line_reader` function and adding a new line of code `includes = []` on the function would have different code outcome. 
So it becomes like this:
```python
def line_reader(lines):
	includes = []
	...
```
huh, python anomalies. i don't understand my code.

How do I document this code?
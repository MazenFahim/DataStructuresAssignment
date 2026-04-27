# 🧮 Problem 5 Q1: Mathematical Expression Evaluator

## 📌 What This Code Does

Evaluates a **math expression given as a string** — handling digits, `+`, `-`, parentheses, spaces, and the tricky **unary minus** — without using any built-in `eval()` function.

```
Input:  " -(2 + 2) + 10"
Output: 6
```

The approach: convert the infix expression into **postfix (Reverse Polish Notation)**, then evaluate it using a stack.

---

## 🏗️ Class Structure

```
Solution
├── operators (stack<char>)  → holds pending operators during conversion
├── postfix (vector<int>)    → stores the postfix sequence
├── sum (int)                → stores the final result
│
├── evaluate(infix_input)    → entry point: converts then evaluates
├── infixToPostfix(...)      → converts infix string to postfix vector
└── print(sum)               → prints the result
```

---

## 🔄 Two-Phase Approach

### Phase 1 — Infix → Postfix

Converts `"2 + 3"` into a postfix sequence like `[2, 3, -1]`

> 📖 **Postfix (RPN)** means operators come *after* their operands.
> `2 + 3` becomes `2 3 +` — no parentheses needed, order is unambiguous.

### Phase 2 — Evaluate Postfix

Reads the postfix sequence using a number stack, applying operators as they appear.

---

## 🗺️ Operator Encoding

Since operators and numbers share the same `vector<int>`, operators are encoded as **special negative values** that no real number would be:

| Value | Meaning |
|---|---|
| `-1` | `+` (addition) |
| `-2` | `-` (subtraction) |
| `0+` | Any non-negative number |

> ⚠️ **Why this works:** The problem guarantees valid expressions, so no operand will ever be negative going into the postfix vector — negatives are produced later by the evaluator, not stored.

---

## ⚙️ Infix to Postfix — Shunting Yard Algorithm

The `infixToPostfix()` function processes the string character by character:

### Spaces → Skip
```cpp
if (c == ' ') continue;
```

### Numbers → Parse multi-digit, push to postfix
```cpp
int number = c - '0';
while (i + 1 < size && isdigit(infix_input[i + 1]))
    number = number * 10 + (infix_input[++i] - '0');
postfix.push_back(number);
```
> ⚠️ The inner `while` loop keeps consuming digits to correctly handle numbers like `100` or `200` as a single token, not three separate digits.

### `(` → Push to operator stack
Parentheses act as a **barrier** — operators won't pop past them.

### `)` → Pop operators until matching `(`
```cpp
while (operators.top() != '(') {
    // flush operators to postfix
}
operators.pop(); // discard the '('
```

### `+` or `-` (binary) → Pop same-precedence operators first
Since `+` and `-` have **equal precedence** and are **left-associative**, any pending `+`/`-` on the stack must be flushed before pushing the new one.

```
Expression: 10 - 4 + 2
When we see '+': stack has '-', so pop '-' first → then push '+'
Postfix result: [10, 4, -2, 2, -1]  ✅ correct left-to-right order
```

---

## ➖ Unary Minus Handling

This is the trickiest part. A `-` is **unary** (not binary) in two situations:

| Situation | Example | Detection |
|---|---|---|
| Start of expression | `-5 + 3` | `postfix.empty() && operators.empty()` |
| Right after `(` | `(-5 + 3)` | `operators.top() == '('` |

### The Fix — Inject a phantom `0`

```cpp
if (isUnary && c == '-') {
    postfix.push_back(0);  // pretend there's a 0 before the minus
    operators.push(c);     // treat '-' as normal binary subtraction
    continue;
}
```

`-(2+2)` is secretly rewritten as `0-(2+2)`.
The evaluator never knows it was unary — it just sees a normal subtraction.

### Full trace for `-(2 + 2) + 10`:
```
c='-'  → unary! push 0      postfix=[0]         ops=['-']
c='('  → push               postfix=[0]         ops=['-','(']
c='2'  → push number        postfix=[0,2]       ops=['-','(']
c='+'  → binary (top='(')   postfix=[0,2]       ops=['-','(','+']
c='2'  → push number        postfix=[0,2,2]     ops=['-','(','+']
c=')'  → pop '+' → pop '('  postfix=[0,2,2,-1]  ops=['-']
c='+'  → pop '-'            postfix=[0,2,2,-1,-2] ops=['+']
c=10   → push number        postfix=[0,2,2,-1,-2,10] ops=['+']
end    → pop '+'            postfix=[0,2,2,-1,-2,10,-1]
```

---

## 📊 Postfix Evaluation

Reads the postfix vector left to right with a number stack:

```
Token  | Action              | Stack
-------|---------------------|-------
  0    | push                | [0]
  2    | push                | [0, 2]
  2    | push                | [0, 2, 2]
 -1    | pop 2,2 → push 4    | [0, 4]
 -2    | pop 4,0 → push 0-4  | [-4]
 10    | push                | [-4, 10]
 -1    | pop 10,-4 → push 6  | [6]   ✅
```

> ⚠️ **Order matters for subtraction!** The code always pops `right` first, then `left`, and computes `left - right`. Getting this backwards would give wrong results.

```cpp
const int right = numbers.top(); numbers.pop();
const int left  = numbers.top(); numbers.pop();
numbers.push(left - right);
```

---

## 🧪 Test Cases

| Expression | Expected Output |
|---|---|
| `"2 + 3"` | `5` |
| `"10 - 4 + 2"` | `8` |
| `"(2 + 3) - 1"` | `4` |
| `"100 + 200"` | `300` |
| `" -(2 + 2) + 10"` | `6` |
| `"3 - (2 + 6)"` | `-5` |

---

## 🧩 Edge Cases Handled

- ✅ **Leading/trailing spaces** — skipped with `continue`
- ✅ **Multi-digit numbers** — inner while loop in digit parsing
- ✅ **Nested parentheses** — operator stack handles any depth
- ✅ **Unary minus at start** — phantom `0` injection
- ✅ **Unary minus after `(`** — same `0` injection trick
- ✅ **State reset between calls** — `evaluate()` clears both `operators` and `postfix` at the start

> ⚠️ **Unary plus is NOT handled** — as per the problem constraints, unary `+` is considered invalid input and will fall through to the binary path, potentially causing incorrect results.

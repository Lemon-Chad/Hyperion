# Language Specification

#### TODO
- More conditionals (Switch?)
- Loops
- Functions
- Classes
- Libraries..?

## Keywords

| Keyword | Purpose                                     |
|:-------:|:--------------------------------------------|
|   if    | Indicates an if statement                   |
|   els   | Indicates an else branch of an if statement |
|   fun   | Indicates a function definition will follow |
|   cls   | Indicates a class definition will follow    |
|   let   | Indicates a variable definition will follow |
|   val   | Indicates a constant definition will follow |
|   nll   | Represents a null value                     |

---

## Variables
```hyperion
let variable: type = value;
let variable: type; // Defaults to nll.
let variable: type!! = value; // Double bang means nll safety.

val constant = value; // Defines a constant value.
```

---

## Conditional Expressions

```hyperion
A == B          // Basic equality.
A != B          // Basic inequality.
A <=> B         // Type coersion equality.

A < B           // Basic inequality (the other kind).
A < B < C       // Compound inequalities supported.

!A              // Inverse of A.
A || B          // A or B.
A && B          // A and B.
```

---

## Conditional Statements

```hyperion
A ==> B; // If A is true, B is executed.
         // Both are expressions.

// Self explanatory demos below.

if A ...
els if B...
els ...

if A {
    ...
} els {
    ...
}
```

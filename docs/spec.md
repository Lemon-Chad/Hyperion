# Language Specification

#### TODO
- More conditionals (Switch?)
- Classes
- Libraries..?

## Keywords

|  Keyword  | Purpose                                     |
|:---------:|:--------------------------------------------|
|    if     | Indicates an if statement                   |
|    els    | Indicates an else branch of an if statement |
|    fun    | Indicates a function definition will follow |
|    cls    | Indicates a class definition will follow    |
|    let    | Indicates a variable definition will follow |
|    val    | Indicates a constant definition will follow |
|    nll    | Represents a null value                     |
|    for    | Indicates a for loop will follow            |
|   while   | Indicates a while loop will follow          |
|    do     | Indicates a do-while loop will follow       |

---

## Variables
```hyperion
let variable: type = value
let variable: type // Defaults to nll.
let variable: type!! = value // Double bang means nll safety.

val constant = value // Defines a constant value.
```

---

## Functions

```hyperion
fun sayHi(name: string) {
    console.log("Hi " + name)
}

sayHi("Mastadons")

// Type assumption for default arguments
fun sayBye(name = "LemonChad") {
 console.log("Hi " + name);
}

sayBye()

// Generics, T extends Number
fun add<T::Number>(a: T, b: T) -> T {
 return a + b
}

console.log(add(2.3, 4.7));
```

---

## Printing
```hyperion
console.log("Hello!") // Cool
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

## Loops

```hyperion
while (x) {
    ...
}

do {
    ...
} while (x)

for (a; b; c) {
    ...
}

// Desugars into
a
while (b) {
    ...
    c
}
```

--

## Conditional Statements

```hyperion
A ==> B // If A is true, B is executed.
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

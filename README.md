# expression_parser Library

Public API: `expression_parser::evaluate(std::string expression)` returns the evaluated numeric result as a string.

Supported features:
- Operators: `+ - * / ^` (power, right associative)
- Unary plus & minus
- Parentheses `( )`
- Functions: `log` (natural), `ln`, `sqrt`, `sin`, `cos`, `tan`, `exp`
- Integer & decimal literals (e.g. `12`, `23.23`, `.5`, `5.`)
- Whitespace ignored

Error Handling:
- Throws `std::runtime_error` with descriptive messages for syntax, domain, or division-by-zero errors.

Example:
```cpp
#include <iostream>
#include "expression_parser.hpp"

int main() {
    std::string expr = "12 + 23.23 - 4 ^ 1 * (2 + log(2))";
    std::cout << expression_parser::evaluate(expr) << "\n";
}
```

Build:
```bash
cmake -S . -B build
cmake --build build --config Release
```

Install (optional):
```bash
cmake --install build --prefix install
```

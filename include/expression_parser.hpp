// Public API for the expression parser library.
// Use evaluate() to parse and evaluate a mathematical expression and
// obtain the numeric result as a string (using default formatting).
// Supported operators (with standard precedence & associativity):
//   +, -, *, /, ^ (power)
// Unary: +, -
// Parentheses: (, )
// Functions: log (natural logarithm), ln (alias), sqrt, sin, cos, tan, exp
// Numbers: integer and decimal literals (e.g., 12, 23.23, .5, 5.)
// Whitespace is ignored.
// Errors result in throwing std::runtime_error with a descriptive message.

#pragma once
#include <string>
#include <stdexcept>

typedef std::string String;

namespace expression_parser {
	String evaluate(String expression);
}

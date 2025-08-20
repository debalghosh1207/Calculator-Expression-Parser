#pragma once
#include "tokenizer.hpp"
#include <vector>
#include <cmath>

namespace internal {

class Parser {
public:
    explicit Parser(Tokenizer tk) : tk_(std::move(tk)) {}
    double parse_expression();
    bool at_end();
private:
    double parse_add_sub();
    double parse_mul_div();
    double parse_power();
    double parse_unary();
    double parse_primary();
    static double eval_function(const std::string &name, const std::vector<double> &args);
    Tokenizer tk_;
};

// Convenience free function
inline double parse_and_evaluate(const std::string &expr) {
    Parser p{Tokenizer(expr)}; // braces avoid vexing-parse
    double result = p.parse_expression();
    if(!p.at_end()) throw std::runtime_error("Unexpected trailing tokens");
    return result;
}

} // namespace internal

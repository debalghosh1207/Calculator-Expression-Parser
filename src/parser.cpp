#include "parser.hpp"
#include <stdexcept>

namespace internal {

double Parser::parse_expression() { return parse_add_sub(); }
bool Parser::at_end() { return tk_.peek().type == TokenType::End; }

double Parser::parse_add_sub() {
    double lhs = parse_mul_div();
    while(true) {
        Token t = tk_.peek();
        if(t.type == TokenType::Plus) { tk_.consume(); lhs += parse_mul_div(); }
        else if(t.type == TokenType::Minus) { tk_.consume(); lhs -= parse_mul_div(); }
        else break;
    }
    return lhs;
}

double Parser::parse_mul_div() {
    double lhs = parse_power();
    while(true) {
        Token t = tk_.peek();
        if(t.type == TokenType::Star) { tk_.consume(); lhs *= parse_power(); }
        else if(t.type == TokenType::Slash) { tk_.consume(); double rhs = parse_power(); if(rhs == 0.0) throw std::runtime_error("Division by zero"); lhs /= rhs; }
        else break;
    }
    return lhs;
}

double Parser::parse_power() {
    double base = parse_unary();
    Token t = tk_.peek();
    if(t.type == TokenType::Caret) { tk_.consume(); double exp = parse_power(); base = std::pow(base, exp); }
    return base;
}

double Parser::parse_unary() {
    Token t = tk_.peek();
    if(t.type == TokenType::Plus) { tk_.consume(); return parse_unary(); }
    if(t.type == TokenType::Minus) { tk_.consume(); return -parse_unary(); }
    return parse_primary();
}

double Parser::parse_primary() {
    Token t = tk_.peek();
    if(t.type == TokenType::Number) { tk_.consume(); return t.numberValue; }
    if(t.type == TokenType::LParen) {
        tk_.consume();
        double val = parse_expression();
        if(tk_.peek().type != TokenType::RParen) throw std::runtime_error("Expected ')'");
        tk_.consume();
        return val;
    }
    if(t.type == TokenType::Identifier) {
        tk_.consume();
        std::string name = t.text;
        if(tk_.peek().type == TokenType::LParen) {
            tk_.consume();
            std::vector<double> args;
            if(tk_.peek().type != TokenType::RParen) {
                while(true) {
                    args.push_back(parse_expression());
                    if(tk_.peek().type == TokenType::Comma) { tk_.consume(); continue; }
                    break;
                }
            }
            if(tk_.peek().type != TokenType::RParen) throw std::runtime_error("Expected ')' after arguments");
            tk_.consume();
            return eval_function(name, args);
        }
        throw std::runtime_error("Unexpected identifier: " + name);
    }
    throw std::runtime_error("Unexpected token: '" + t.text + "'");
}

double Parser::eval_function(const std::string &name, const std::vector<double> &args) {
    auto require_arity = [&](size_t n){ if(args.size() != n) throw std::runtime_error("Function '" + name + "' expects " + std::to_string(n) + " argument(s)"); };
    if(name == "log" || name == "ln") { require_arity(1); if(args[0] <= 0) throw std::runtime_error("log domain error"); return std::log(args[0]); }
    if(name == "sqrt") { require_arity(1); if(args[0] < 0) throw std::runtime_error("sqrt domain error"); return std::sqrt(args[0]); }
    if(name == "sin") { require_arity(1); return std::sin(args[0]); }
    if(name == "cos") { require_arity(1); return std::cos(args[0]); }
    if(name == "tan") { require_arity(1); return std::tan(args[0]); }
    if(name == "exp") { require_arity(1); return std::exp(args[0]); }
    throw std::runtime_error("Unknown function: " + name);
}

} // namespace internal

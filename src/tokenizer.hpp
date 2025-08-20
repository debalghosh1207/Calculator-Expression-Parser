#pragma once
#include <string>
#include <stdexcept>

namespace internal {

enum class TokenType {
    Number,
    Plus, Minus, Star, Slash, Caret,
    LParen, RParen,
    Identifier,
    Comma,
    End
};

struct Token {
    TokenType type;
    std::string text;
    double numberValue{};
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string &src) : src_(src) {}
    Token peek();
    Token consume();
private:
    Token next();
    void skip_ws();
    Token lex_number();
    Token lex_identifier();
    Token make(TokenType t, std::string txt);
    std::string src_;
    size_t pos_ = 0;
    bool hasPeek_ = false;
    Token lookahead_{};
};

} // namespace internal

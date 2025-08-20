#include "tokenizer.hpp"
#include <cctype>
#include <cstdlib>

namespace internal {

Token Tokenizer::make(TokenType t, std::string txt) { return Token{t, std::move(txt), 0.0}; }

void Tokenizer::skip_ws() { while(pos_ < src_.size() && std::isspace(static_cast<unsigned char>(src_[pos_]))) ++pos_; }

Token Tokenizer::lex_number() {
    size_t start = pos_;
    bool sawDot = false;
    while(pos_ < src_.size()) {
        char c = src_[pos_];
        if(c == '.') { if(sawDot) break; sawDot = true; ++pos_; continue; }
        if(!std::isdigit(static_cast<unsigned char>(c))) break;
        ++pos_;
    }
    std::string t = src_.substr(start, pos_-start);
    if(t == "." || t.empty()) throw std::runtime_error("Invalid numeric literal: " + t);
    return Token{TokenType::Number, t, std::stod(t)};
}

Token Tokenizer::lex_identifier() {
    size_t start = pos_;
    while(pos_ < src_.size()) {
        char c = src_[pos_];
        if(std::isalnum(static_cast<unsigned char>(c)) || c == '_') ++pos_; else break;
    }
    std::string t = src_.substr(start, pos_-start);
    return Token{TokenType::Identifier, t, 0.0};
}

Token Tokenizer::next() {
    skip_ws();
    if(pos_ >= src_.size()) return make(TokenType::End, "");
    char c = src_[pos_];
    if(std::isdigit(static_cast<unsigned char>(c)) || c == '.') return lex_number();
    if(std::isalpha(static_cast<unsigned char>(c)) || c == '_') return lex_identifier();
    ++pos_;
    switch(c) {
        case '+': return make(TokenType::Plus, "+");
        case '-': return make(TokenType::Minus, "-");
        case '*': return make(TokenType::Star, "*");
        case '/': return make(TokenType::Slash, "/");
        case '^': return make(TokenType::Caret, "^");
        case '(': return make(TokenType::LParen, "(");
        case ')': return make(TokenType::RParen, ")");
        case ',': return make(TokenType::Comma, ",");
    }
    throw std::runtime_error(std::string("Unexpected character: ") + c);
}

Token Tokenizer::peek() { if(!hasPeek_) { lookahead_ = next(); hasPeek_ = true; } return lookahead_; }
Token Tokenizer::consume() { if(hasPeek_) { hasPeek_ = false; return lookahead_; } return next(); }

} // namespace internal

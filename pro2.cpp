#include <iostream>
#include <vector>
#include <string>
#include <regex>

enum TokenType { KEYWORD, IDENTIFIER, NUMBER, OPERATOR, DELIMITER };

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> lex(const std::string& input) {
    std::vector<Token> tokens;
    std::regex tokenPatterns("(let|if)|([a-zA-Z_][a-zA-Z0-9_]*)|(\\d+)|(\\+|\\-|\\*|\\/|>|<|==|!=)|(\\{|\\}|\\(|\\)|;)");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), tokenPatterns);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        if (match[1].matched) tokens.push_back({KEYWORD, match.str()});
        else if (match[2].matched) tokens.push_back({IDENTIFIER, match.str()});
        else if (match[3].matched) tokens.push_back({NUMBER, match.str()});
        else if (match[4].matched) tokens.push_back({OPERATOR, match.str()});
        else if (match[5].matched) tokens.push_back({DELIMITER, match.str()});
    }
    return tokens;
}

int main() {
    std::string code = "let x = 10; if (x > 5) { x = x + 1; }";
    std::vector<Token> tokens = lex(code);
    
    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << std::endl;
    }
}

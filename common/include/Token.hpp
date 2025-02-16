#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
  // Keywords
  KW_INT,
  KW_FLOAT,
  KW_CHAR,
  KW_DOUBLE,
  KW_BOOL,
  KW_RETURN,
  KW_IF,
  KW_ELSE,
  KW_WHILE,
  KW_FOR,
  KW_SWITCH,
  KW_CASE,
  KW_DEFAULT,
  KW_ENUM,
  KW_UNION,
  KW_STRUCT,
  // Operators
  OP_PLUS,
  OP_MINUS,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_ASSIGN,
  OP_PLUS_ASSIGN,
  OP_MINUS_ASSIGN,
  OP_MULTIPLY_ASSIGN,
  OP_DIVIDE_ASSIGN,
  OP_EQUAL,
  OP_NOT_EQUAL,
  OP_LESS,
  OP_GREATER,
  OP_LESS_EQUAL,
  OP_GREATER_EQUAL,
  OP_LOGICAL_AND,
  OP_LOGICAL_OR,
  OP_BITWISE_AND,
  OP_BITWISE_OR,
  OP_BITWISE_XOR,
  OP_LEFT_SHIFT,
  OP_RIGHT_SHIFT,
  // Delimiters
  DELIM_SEMICOLON,
  DELIM_COMMA,
  DELIM_LPAREN,
  DELIM_RPAREN,
  DELIM_LBRACE,
  DELIM_RBRACE,
  DELIM_COLON,
  DOT,
  // Literals
  LITERAL_INT,
  LITERAL_FLOAT,
  LITERAL_DOUBLE,
  LITERAL_CHAR,
  // Identifiers, end-of-file, unknown.
  IDENTIFIER,
  EOF_TOKEN,
  UNKNOWN
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;
  int column;
};

#endif // TOKEN_HPP

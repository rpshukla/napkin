#ifndef NAPKIN_PARSER_H_
#define NAPKIN_PARSER_H_

#include <vector>
#include <iostream>

#include "AST.h"
#include "nexception.h"
#include "token.h"

namespace napkin {

/**
 * Recursive descent parser
 */
class Parser {
public:
  Parser(std::vector<Token> t_tokens) : tokens(t_tokens) {
    hadError = false;
  };
  std::vector<Stmt *> parse();
  bool hadError;

private:
  std::vector<Token> tokens;
  unsigned int current = 0; // index of current token

  // Each of these methods correspond to a rule in ebnf.txt
  Stmt *stmt();
  Stmt *exprStmt();
  Stmt *outputStmt();
  std::vector<Stmt *> blockStmt();
  Stmt *ifStmt();
  Stmt *whileStmt();
  Stmt *returnStmt();
  
  Expr *expr();
  Expr *lambdaExpr();
  Expr *assignExpr();
  Expr *_or();
  Expr *_and();
  Expr *equality();
  Expr *comparison();
  Expr *addition();
  Expr *multiplication();
  Expr *exponentiation();
  Expr *unary();
  Expr *call();
  Expr *finishCall(Expr *callee);
  Expr *primary();

  // Helper methods
  void ignoreNewlines();
  void checkTerminator();
  bool match(TokenType type);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token peek(unsigned int n);
  Token previous();
};

} // namespace napkin

#endif

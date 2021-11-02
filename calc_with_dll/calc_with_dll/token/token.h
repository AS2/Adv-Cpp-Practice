#pragma once

typedef enum {
  OPER = 0,
  NUM
} tokenType_t;

typedef struct {
  char tokenId;
  std::string tokenName;
} operatorValue_t;

typedef struct {
  operatorValue_t operValue;
  double numValue;
} contain_t;

typedef struct token_t {
  tokenType_t tokenType;
  contain_t value;
} token_t;

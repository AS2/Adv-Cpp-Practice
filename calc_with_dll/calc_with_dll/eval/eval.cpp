#include <stack>
#include "eval.h"
#include "../error/error.h"

/**
* Default 'eval' constructor
* @param[in] operators - operators map
* @param[in] tokensPolIS - tokens queue in RPN
* @warning Fill error in 'calc_error' struct if some operators cant execute by some reasons
* @return result of value
*/
double eval::evalvate(const std::map<char, std::unique_ptr<def_operator>>& operators, std::queue<token_t>& tokensPolIS) {
  std::stack<token_t> tokens;
  token_t token, tokenNum1, tokenNum2;
  def_operator* tmp_op;

  while (!tokensPolIS.empty()) {
    token = tokensPolIS.front();
    tokensPolIS.pop();

    if (token.tokenType == NUM)
      tokens.push(token);
    else {
      tmp_op = operators.at(token.value.operValue.tokenId).get();

      if (!tmp_op->isOperUnar()) {
        tokenNum2 = tokens.top();
        tokens.pop();
      }
      tokenNum1 = tokens.top();
      tokens.pop();

      tokenNum1.value.numValue = tmp_op->executeOperation(tokenNum1.value.numValue, tokenNum2.value.numValue, calc_error::getInstance());

      if (calc_error::getInstance().errorType != calc_error::NO_ERR)
        return -1;

      tokens.push(tokenNum1);
    }
  }
  tokenNum1 = tokens.top();
  tokens.pop();
  
  if (!tokens.empty()) {
    calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "'opers' is not ended in Eval func");
    return 0;
  }
  return tokenNum1.value.numValue;
}
#include "../error/error.h"
#include "parser.h"

bool parser::CheckAssoc(const def_operator* const op1, const def_operator* const op2) {
  return (op1->GetPriority() == op2->GetPriority() && (op1->isOperRightAssoc())) ? op1->GetPriority() > op2->GetPriority() : op1->GetPriority() >= op2->GetPriority();
}

void parser::DropOpers(const std::map<char, std::unique_ptr<def_operator>>& operators, const def_operator* const op) {
  token_t token;

  while (!stack2.empty() && CheckAssoc(operators.at(stack2.top().value.operValue.tokenId).get(), op) != 0) {
    token = stack2.top();
    stack2.pop();
    stack1.push(token);
  }
}

/**
* Parse queue in 'PARSE_PREFIX' state
* @param[in] operators - supportive operators map
* @param[in] op - operator to drop operators from stack
*/
parser::state_t parser::ParsePrefix(const std::map<char, std::unique_ptr<def_operator>>& operators, token_t& token) {
  def_operator* tmp_oper1;

  if (token.tokenType == NUM) {
    stack1.push(token);
    return STATE_SUFFIX;
  }
  else if (token.tokenType == OPER && token.value.operValue.tokenName == "(")
    stack2.push(token);
  else if (token.tokenType == OPER && token.value.operValue.tokenName == "-") {
    token.value.operValue.tokenId = '!';
    stack2.push(token);
  }
  else if (token.tokenType == OPER) {
    tmp_oper1 = operators.at(token.value.operValue.tokenId).get();
    if (tmp_oper1->isOperUnar())
      stack2.push(token);
    else {
      calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Wait for number, unar operator or '('");
      return STATE_END;
    }
  }
  
  return STATE_PREFIX;
}

/**
  * Parse queue in 'PARSE_SUFFIX' state
  * @param[in] operators - supportive operators map
  * @param[in] op - operator to drop operators from stack
  */
parser::state_t parser::ParseSuffix(const std::map<char, std::unique_ptr<def_operator>>& operators, token_t& token) {
  if (token.tokenType == OPER && token.value.operValue.tokenName != "(") {
    DropOpers(operators, operators.at(token.value.operValue.tokenId).get());
    if (token.value.operValue.tokenName != ")") {
      stack2.push(token);
      return STATE_PREFIX;
    }
    else {
      if (stack2.empty()) {
        calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "'(' bracket is missing somewhere");
        return STATE_END;
      }
      else {
        token = stack2.top();
        stack2.pop();
        return STATE_SUFFIX;
      }
    }
  }
  else {
    calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Wait for operation or ')'");
    return STATE_END;
  }
}

/**
* Parse queue in 'PARSE_DONE' state
* @param[in] operators - supportive operators map
* @param[in] op - operator to drop operators from stack
*/
void parser::ParseDone(const std::map<char, std::unique_ptr<def_operator>>& operators) {
  DropOpers(operators, operators.at(')').get());
  if (!stack2.empty()) {
    calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "')' bracket");
    return;
  }
  while (!stack1.empty()) {
    stack2.push(stack1.top());
    stack1.pop();
  }
  while (!stack2.empty()) {
    tokenPolIS.push(stack2.top());
    stack2.pop();
  }
}

void parser::parseQueue(const std::map<char, std::unique_ptr<def_operator>>& operators, std::queue<token_t>& tokensToParse) {
  state_t parseState = STATE_PREFIX;
  token_t token;

  while (parseState != STATE_END) {
    if (parseState <= STATE_SUFFIX) {
      if (tokensToParse.empty()) {
        if (parseState == STATE_SUFFIX)
          parseState = STATE_DONE;
        else {
          calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Unexpected end-of-expression");
          parseState = STATE_END;
        }
      }
      else {
        token = tokensToParse.front();
        tokensToParse.pop();
      }
    }

    switch (parseState) {
    case STATE_PREFIX:
      parseState = ParsePrefix(operators, token);
      break;
    case STATE_SUFFIX:
      parseState = ParseSuffix(operators, token);
      break;
    case STATE_DONE:
      ParseDone(operators);
      parseState = STATE_END;
      break;
    }
  }
}

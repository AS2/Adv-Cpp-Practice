#include "../error/error.h"
#include "parser.h"

int parser::CheckAssoc(std::shared_ptr<def_operator> const &op1, std::shared_ptr<def_operator> const& op2) {
  return (op1->GetPriority() == op2->GetPriority() && (op1->GetName() == "^")) ? op1->GetPriority() > op2->GetPriority() : op1->GetPriority() >= op2->GetPriority();
}

void parser::DropOpers(const std::map<char, std::shared_ptr<def_operator>>& operators, std::shared_ptr<def_operator> const& op) {
  token_t token;

  while (!stack2.empty() && CheckAssoc(operators.at(stack2.top().value.operValue.tokenId), op) != 0) {
    token = stack2.top();
    stack2.pop();
    stack1.push(token);
  }
}

void parser::parseQueue(const std::map<char, std::shared_ptr<def_operator>>& operators, std::queue<token_t>& tokensToParse) {
  enum {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state = STATE_PREFIX;
  token_t token;
  std::shared_ptr<def_operator> tmp_oper1;

  while (state != STATE_END) {
    if (state <= STATE_SUFFIX) {
      if (tokensToParse.empty()) {
        if (state == STATE_SUFFIX) {
          state = STATE_DONE;
        }
        else {
          calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Unexpected end-of-expression");
          state = STATE_END;
        }
      }
      else {
        token = tokensToParse.front();
        tokensToParse.pop();
      }
    }

    switch (state) {
    case STATE_PREFIX:
      if (token.tokenType == NUM) {
        state = STATE_SUFFIX;
        stack1.push(token);
      }
      else if (token.tokenType == OPER && token.value.operValue.tokenName == "(")
        stack2.push(token);
      else if (token.tokenType == OPER && token.value.operValue.tokenName == "-") {
        token.value.operValue.tokenId = '!';
        stack2.push(token);
      }
      else if (token.tokenType == OPER) {
        tmp_oper1 = operators.at(token.value.operValue.tokenId);
        if (tmp_oper1->isOperUnar())
          stack2.push(token);
        else {
          calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Wait for number, unar operator or '('");
          state = STATE_END;
        }
      }
      break;
    case STATE_SUFFIX:
      if (token.tokenType == OPER && token.value.operValue.tokenName != "(") {
        DropOpers(operators, operators.at(token.value.operValue.tokenId));
        if (token.value.operValue.tokenName != ")") {
          stack2.push(token);
          state = STATE_PREFIX;
        }
        else {
          if (stack2.empty()) {
            calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Wtf? Brackets? Ew... Check some brackets, man");
            state = STATE_END;
          }
          else {
            token = stack2.top();
            stack2.pop();
          }
        }
      }
      else {
        calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "Wait for operation or ')'");
        state = STATE_END;
      }
      break;
    case STATE_DONE:
      DropOpers(operators, operators.at(')'));
      if (!stack2.empty()) {
        calc_error::getInstance().UpdateError(calc_error::PARSER_ERR, "')' bracket");
        state = STATE_END;
      }
      while (!stack1.empty()) {
        token = stack1.top();
        stack1.pop();
        stack2.push(token);
      }
      while (!stack2.empty()) {
        token = stack2.top();
        stack2.pop();
        tokenPolIS.push(token);
      }
      state = STATE_END;
      break;
    }
  }
}

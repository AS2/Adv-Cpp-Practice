#pragma once

#include <map>
#include <queue>
#include <memory>
#include <stack>
#include <string>

#include "../operators/operator.h"
#include "../token/token.h"

/**
@brief Parser class
@details Parser class, which parse token queue in Infix order into token queue in Reverse Polish Notation
*/
class parser {
private:
  std::stack<token_t> stack1, stack2;  ///< some helpful stacks to reverse
  std::queue<token_t> tokenPolIS;      ///< tokens queue in RPN

  /**
  * Check assoc function
  * @param[in] op1 - first operator
  * @param[in] op2 - second operator
  * @return - 1 if assoc, 0 if not
  */
  int CheckAssoc(std::shared_ptr<def_operator> const& op1, std::shared_ptr<def_operator> const& op2);

  /**
  * Check assoc function
  * @param[in] operators - supportive operators map
  * @param[in] op - operator to drop operators from stack
  */
  void DropOpers(const std::map<char, std::shared_ptr<def_operator>>& operators, std::shared_ptr<def_operator> const& op);
public:
  /**
  * Default parser constructor
  */
  parser() {};

  /**
  * Parse tokens queue function
  * @param[in] operators - supportive operators map
  * @param[in] tokensToParse - tokens queue to parse
  */
  void parseQueue(const std::map<char, std::shared_ptr<def_operator>>& operators, std::queue<token_t>& tokensToParse);

  /**
  * Parse tokens queue function
  * @return 'std::queue<token_t>' tokens queue in RPN
  */
  std::queue<token_t>& GetTokensPolIS() { return tokenPolIS; };
};

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
  * Different parse state: STATE_PREFIX - from queue taken prefix, STATE_SUFFIX - from queue taken suffix, STATE_DONE - all queue parsed into stacks and ready to build into one queue, STATE_END - end parsing
  */
  typedef enum {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state_t;

  /**
  @brief Check assoc function
  @details Check right association of operators, considering the associativity of operators: if operator is right asscoiative, than return boolean of 'op1->priority() > op2->priority()', if left priority - 'op1->priority() >= op2->priority()'
  @param[in] op1 - first operator
  @param[in] op2 - second operator
  @return - 1 if assoc, 0 if not
  */
  bool CheckAssoc(const def_operator *const op1, const def_operator *const op2);

  /**
  @brief Drop operators from 'Stack2' to 'Stack1'
  @details Drop operators from 'Stack2' to 'Stack1' while priorite of 'op' operator is less (or not bigger) than operators from 'Stack2'
  @param[in] operators - supportive operators map
  @param[in] op - operator to drop operators from stack
  */
  void DropOpers(const std::map<char, std::unique_ptr<def_operator>>& operators, const def_operator *const op);

  /**
  * Parse queue in 'STATE_PREFIX' parse state
  * @param[in] operators - supportive operators map
  * @param[in] op - operator to drop operators from stack
  */
  state_t ParsePrefix(const std::map<char, std::unique_ptr<def_operator>>& operators, token_t& token);

  /**
  * Parse queue in 'STATE_SUFFIX' parse state
  * @param[in] operators - supportive operators map
  * @param[in] op - operator to drop operators from stack
  */
  state_t ParseSuffix(const std::map<char, std::unique_ptr<def_operator>>& operators, token_t& token);

  /**
  * Parse queue in 'STATE_DONE' parse state
  * @param[in] operators - supportive operators map
  * @param[in] op - operator to drop operators from stack
  */
  void ParseDone(const std::map<char, std::unique_ptr<def_operator>>& operators);
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
  void parseQueue(const std::map<char, std::unique_ptr<def_operator>>& operators, std::queue<token_t>& tokensToParse);

  /**
  * Parse tokens queue function
  * @return 'std::queue<token_t>' tokens queue in RPN
  */
  std::queue<token_t>& GetTokensPolIS() { return tokenPolIS; };
};

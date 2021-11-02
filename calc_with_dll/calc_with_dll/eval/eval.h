#pragma once

#include <memory>
#include <queue>
#include <map>

#include "../operators/operator.h"
#include "../token/token.h"

class eval {
private:
public:
  eval() {};

  double evalvate(const std::map<char, std::shared_ptr<def_operator>>& operators, std::queue<token_t>& tokensPolIS);
};

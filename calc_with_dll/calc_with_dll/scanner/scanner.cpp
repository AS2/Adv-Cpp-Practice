#include "scanner.h"

/**
  * Generate and fill operators names and ID's set
  *	@param[in] operators - operators map
  */
void scanner::FillOpersNames(const std::map<char, std::shared_ptr<def_operator>>& operators) {
  for (auto& el : operators)
    if (el.second->GetId() != '!')
      opersNamesAndIDs.emplace(std::pair<std::string, char>(el.second->GetName(), el.second->GetId()));
}

/**
  * Read function(operator) from string
  *	@param[in] strBegin - 'const char*' string position, where operator starts
  * @warning Fill error in 'calc_error' struct if function(operator) doesnt exist
  * @return new 'token_t' token operator
  */
token_t scanner::ReadFunc(const char* strBegin) {
  token_t tokenToReturn;
  int i;

  for (auto& operName : opersNamesAndIDs) {
    const char* c_operName = operName.first.c_str();

    for (i = 0; i < operName.first.length() && strBegin[i] != 0; i++)
      if (c_operName[i] != strBegin[i])
        break;

    if (i == operName.first.length()) {
      tokenToReturn.tokenType = OPER;
      tokenToReturn.value.operValue.tokenName = operName.first;
      tokenToReturn.value.operValue.tokenId = operName.second;
      return tokenToReturn;
    }
  }
  calc_error::getInstance().UpdateError(calc_error::SCANNER_ERR, "Unknown operator");
  return tokenToReturn;
}


/**
  * String scanner function
  *	@param[in] operators - operators map
  *	@param[in] strToParse - string to parse
  * @warning Fill error in 'calc_error' struct if string contains function(operator) which doesnt exist
  */
void scanner::scanString(const std::map<char, std::shared_ptr<def_operator>>& operators, const std::string& strToParse) {
  FillOpersNames(operators);
  token_t newToken;
  int i = 0;
  const char* str = strToParse.c_str(), *strBegin = strToParse.c_str();
  char* end;
  double res;

  while (*str != '\0' && str - strBegin < strToParse.length()) {
    if (*str >= '0' && *str <= '9') {
      res = strtod(str, &end);
      if (errno != 0 || end == str) {
        calc_error::getInstance().UpdateError(calc_error::SCANNER_ERR, "Bad number");
        return;
      }
      str = end;

      newToken.tokenType = NUM;
      newToken.value.numValue = res;

      tokenQueue.push(newToken);
    }
    else {
      newToken = ReadFunc(str);
      if (calc_error::getInstance().errorType != calc_error::NO_ERR)
        return;

      tokenQueue.push(newToken);
      str = str + newToken.value.operValue.tokenName.length();
    }
  }
}
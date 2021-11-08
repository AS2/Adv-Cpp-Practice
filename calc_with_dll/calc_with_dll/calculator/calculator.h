#pragma once

#include <windows.h>

#include <map>
#include <list>
#include <queue>
#include <stack>

#include "../operators/standart_operators.h"
#include "../scanner/scanner.h"
#include "../parser/parser.h"
#include "../eval/eval.h"

#include "../error/error.h"
#include "../token/token.h"

/**
@brief Calculator class
@details Calculator class, which execute evaluating from 'std::string' expression and supports operation from ../DLLs Code/build/plugins
*/
class calculator {
private:
  std::map<char, std::unique_ptr<def_operator>> operatorsMap;  ///< map of all supportive operators
  
  std::list<HMODULE> dlls;                                     ///< list with all opened dlls

  /**
    * Fill operators' map with standart operators
    */
  void FillStandartOperatorsMap(void);

  /**
    * Fill operators' map with one additional operators from dlls
    * @param[in] dllPath - path to additional dll
    */
  void FillOperatorsFromOneDll(const std::string& dllPath);

  /**
    * Fill operators' map with additional operators from dlls from one folder
    * @param[in] dllsPath - path to folder with additional dlls
    */
  void FillOperatorsFromDLLs(const std::string& dllsPath);
public:

  calculator();

  /**
    * calculator constructor
    * @param[in] dllPath - path to folder with additional dlls
    */
  calculator(const std::string& dllPath);
  
  double executeExpression(const std::string& expression);

  ~calculator();
};

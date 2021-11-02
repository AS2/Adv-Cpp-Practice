#include <iostream>
#include <filesystem>

#include "calculator.h"

using DEFOPER = def_operator*(__cdecl*)(void);

/**
  * Fill operators' map with standart operators
  */
void calculator::FillStandartOperatorsMap(void) {
  std::shared_ptr<def_operator> oper = std::make_shared<add_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<substruct_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<multiply_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<divide_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<unar_minus_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<open_bracket_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));

  oper = std::make_shared<close_bracket_operator>();
  operatorsMap.emplace(std::make_pair(oper->GetId(), oper));
}

/**
  * Fill operators' map with one additional operators from dlls
  * @param[in] dllPath - path to additional dll
  */
void calculator::FillOperatorsFromOneDll(const std::string& dllPath) {
  HMODULE dll = LoadLibrary(dllPath.c_str());
  if (dll == nullptr) {
    std::cout << dllPath << ": Can't open dll" << std::endl;
    return;
  }

  DEFOPER DefineOperatorFunc = (DEFOPER)GetProcAddress(dll, "defineOperator");
  if (DefineOperatorFunc == nullptr) {
    std::cout << dllPath << ": Can't find new operator initializer" << std::endl;
    FreeLibrary(dll);
    return;
  }
  dlls.push_back(dll);

  std::shared_ptr<def_operator> newOperator(DefineOperatorFunc());
  operatorsMap.emplace(std::make_pair(newOperator->GetId(), newOperator));
  std::cout << dllPath << ": dll loaded" << std::endl;
}

/**
  * Fill operators' map with additional operators from dlls from one folder
  * @param[in] dllsPath - path to folder with additional dlls
  */
void calculator::FillOperatorsFromDLLs(const std::string& dllsPath) {
  std::filesystem::directory_iterator folder(dllsPath);

  std::cout << "DLL LOADER LOG:" << std::endl;
  std::cout << "Connect plagins from '" << dllsPath << "'" << std::endl;
  for (auto& file : folder) {
    if (file.path().extension().string() != ".dll")
      continue;

    FillOperatorsFromOneDll(file.path().string());
  }
  std::cout << "END LOG" << std::endl << std::endl;
}

/**
  * default calculator constructor
  */
calculator::calculator() {
  FillStandartOperatorsMap();
}

/**
  * calculator constructor
  * @param[in] dllPath - path to folder with additional dlls
  */
calculator::calculator(const std::string& dllPath) {
  FillStandartOperatorsMap();
  FillOperatorsFromDLLs(dllPath);
}

/**
  * Execute evaluating expression
  * @param[in] expression - std::string with expression to evaluate
  * @warning Fill error in 'calc_error' struct if expression has some problems (inknown operators, bracke)
  */
double calculator::executeExpression(const std::string& expression) {
  std::queue<token_t> tokensQueue, tokensPolIS;
  scanner scan;
  parser pars;
  eval evalver;
  double res;

  scan.scanString(operatorsMap, expression);
  if (calc_error::getInstance().errorType != calc_error::NO_ERR)
    return 0;

  pars.parseQueue(operatorsMap, scan.GetTokenQueue());
  if (calc_error::getInstance().errorType != calc_error::NO_ERR)
    return 0;

  res = evalver.evalvate(operatorsMap, pars.GetTokensPolIS());
  if (calc_error::getInstance().errorType != calc_error::NO_ERR)
    return 0;

  return res;
}

/**
  * default calculator destructor
  */
calculator::~calculator() {
  for (auto& dll : dlls)
    FreeLibrary(dll);
}

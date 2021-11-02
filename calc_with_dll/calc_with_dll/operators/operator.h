#pragma once

#include <string>
#include "../error/error.h"

class def_operator {
protected:
  double priority;
  char operatorId;
  bool isUnar;
  std::string operatorName;
  
  def_operator() {};

public:
  char GetId() const { return operatorId; };
  const std::string& GetName() const { return operatorName; };
  double GetPriority() const { return priority; };
  bool isOperUnar() const { return isUnar; };

  virtual double executeOperation(double lValue, double rValue, calc_error& err) = 0;
};


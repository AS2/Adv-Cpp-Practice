#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

class arcsin : public def_operator {
public:
  arcsin() {
    isUnar = true;
    priority = 9;
    operatorId = 'd';
    operatorName = "arcsin";
  };

  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    if (lValue < -1 || lValue > 1) {
      err.UpdateError(calc_error::OPER_ERR, "'arcsin' can evaluate argument between -1 and 1");
      return -1;
    }
    return asin(lValue);
  }
};

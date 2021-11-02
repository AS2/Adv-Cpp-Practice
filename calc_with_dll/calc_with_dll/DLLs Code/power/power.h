#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

class power : public def_operator {
public:
  /**
  * Default 'power' operator constructor
  */
  power() {
    isUnar = false;
    priority = 8;
    operatorId = '^';
    operatorName = "^";
  };

  /**
  * Virtual function of execute operator "^"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    if (lValue == 0 && rValue == 0) {
      err.UpdateError(calc_error::OPER_ERR, "'power' - lValue and rValue can't be zero in one time");
      return 1;
    }
    return pow(lValue, rValue);
  }
};

#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

class arccos : public def_operator {
public:
  /**
  * Default 'arccos' operator constructor
  */
  arccos() {
    isUnar = true;
    priority = 9;
    operatorId = 'b';
    operatorName = "arccos";
  };

  /**
  * Virtual execute function of 'arccos' operator
  * @param[in] lValue - value for unary operator
  * @param[in] rValue - right value for binary operator (none)
  * @param[in] err - error struct to fill if operator takes bad values
  * @warning Fill error in 'calc_error' struct if value not between -1 and 1
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    if (lValue < -1 || lValue > 1) {
      err.UpdateError(calc_error::OPER_ERR, "'arccos' can evaluate argument between -1 and 1");
      return -1;
    }
    return acos(lValue);
  }
};

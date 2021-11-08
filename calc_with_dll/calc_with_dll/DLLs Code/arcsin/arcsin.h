#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

/**
* @brief 'arcsin' operator class
*/
class arcsin : public def_operator {
public:
  /**
  * Default 'arcsin' operator constructor
  */
  arcsin() {
    isUnar = true;
    isRightAssoc = false;
    priority = 9;
    operatorId = 'd';
    operatorName = "arcsin";
  };

  /**
  * Virtual function of execute operator "arcsin"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    if (lValue < -1 || lValue > 1) {
      err.UpdateError(calc_error::OPER_ERR, "'arcsin' can evaluate argument between -1 and 1");
      return -1;
    }
    return asin(lValue);
  }
};

#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

/**
* @brief 'log' of 'e' operator class
*/
class ln : public def_operator {
public:
  /**
  * Default 'ln' operator constructor
  */
  ln() {
    isUnar = true;
    priority = 9;
    operatorId = 'l';
    operatorName = "ln";
  };

  /**
  * Virtual execute function of 'ln' operator
  * @param[in] lValue - value for unary operator
  * @param[in] rValue - right value for binary operator (none)
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return log(lValue);
  }
};

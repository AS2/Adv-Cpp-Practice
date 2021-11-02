#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

/**
* @brief 'sinus' operator class
*/
class sinus : public def_operator {
public:
  /**
  * Default 'sinus' operator constructor
  */
  sinus() {
    isUnar = true;
    priority = 9;
    operatorId = 's';
    operatorName = "sin";
  };

  /**
  * Virtual execute function of 'sin' operator
  * @param[in] lValue - value for unary operator
  * @param[in] rValue - right value for binary operator (none)
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return sin(lValue);
  }
};

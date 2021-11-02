#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

class mod : public def_operator {
public:
  /**
  * Default 'mod' operator constructor
  */
  mod() {
    isUnar = false;
    priority = 5.5;
    operatorId = '%';
    operatorName = "%";
  };

  /**
  * Virtual function of execute operator "%"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return fmod(lValue, rValue);
  }
};

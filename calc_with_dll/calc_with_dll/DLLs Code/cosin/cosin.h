#pragma once
#include "../../operators/operator.h"
#include "../../dllLoader/dllPlugin.h"

/**
* @brief cosin operator class
*/
class cosin : public def_operator {
public:
  /**
  * Default 'cosin' operator constructor
  */
  cosin() {
    isUnar = true;
    isRightAssoc = false;
    priority = 9;
    operatorId = 'c';
    operatorName = "cos";
  };

  /**
  * Virtual function of execute operator "cos"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return cos(lValue);
  }
};

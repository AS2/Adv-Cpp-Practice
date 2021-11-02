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
    priority = 9;
    operatorId = 'c';
    operatorName = "cos";
  };

  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return cos(lValue);
  }
};

#pragma once

#include "operator.h"

/**
* Sum operator
*/
class add_operator : public def_operator {
public:
  /**
  * Default sum operator constructor
  */
  add_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 5;
    operatorId = '+';
    operatorName = "+";
  }

  /**
  * Virtual function of execute operator "+"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return lValue + rValue;
  }
};

/**
* Binary minus operator
*/
class substruct_operator : public def_operator {
public:
  /**
  * Default Binary minus operator constructor
  */
  substruct_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 5;
    operatorId = '-';
    operatorName = "-";
  };
  
  /**
  * Virtual function of execute operator "-"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return lValue - rValue;
  }
};

/**
* Multiply operator
*/
class multiply_operator : public def_operator {
public:
  /**
  * Default multiply operator constructor
  */
  multiply_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 6;
    operatorId = '*';
    operatorName = "*";
  };

  /**
  * Virtual function of execute operator "*"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return lValue * rValue;
  }
};

/**
* Divide operator
*/
class divide_operator : public def_operator {
public:
  /**
  * Default divide operator constructor
  */
  divide_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 6;
    operatorId = '/';
    operatorName = "/";
  };

  /**
  * Virtual function of execute operator "/"
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    if (rValue == 0) {
      err.UpdateError(calc_error::EVAL_ERR, "'/' error^ cannot divide on zero!");
      return -1;
    }
    return lValue / rValue;
  }
};

/**
* Unary minus operator
*/
class unar_minus_operator : public def_operator {
public:
  /**
  * Default unary minus operator constructor
  */
  unar_minus_operator() {
    isUnar = true;
    isRightAssoc = false;
    priority = 7;
    operatorId = '!';
    operatorName = "-";
  };

  /**
  * Virtual function of execute unary operator "-"
  * @param[in] lValue - value for unary
  * @param[in] rValue - right value for binary operator (none)
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    return (-1.0) * lValue;
  }
};

/**
* Open bracket operator
*/
class open_bracket_operator : public def_operator {
public:
  /**
  * Default open bracket operator constructor
  */
  open_bracket_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 0;
    operatorId = '(';
    operatorName = "(";
  }

  /**
  * Virtual function of execute operator "("
  * @warning '(' and ')' are not operators! They are only childs of 'def_operator' only because they work like operators with some exception
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute (none)
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    err.UpdateError(calc_error::EVAL_ERR, "'(' - is not an operator!");
    return -1;
  }
};

/**
* Close bracket operator
*/
class close_bracket_operator : public def_operator {
public:
  /**
  * Default close bracket operator constructor
  */
  close_bracket_operator() {
    isUnar = false;
    isRightAssoc = false;
    priority = 1;
    operatorId = ')';
    operatorName = ")";
  };

  /**
  * Virtual function of execute operator ")"
  * @warning '(' and ')' are not operators! They are only childs of 'def_operator' only because they work like operators with some exception
  * @param[in] lValue - left value for binary operator
  * @param[in] rValue - right value for binary operator
  * @param[in] err - error struct to fill if operator takes bad values
  * @return result of operator execute (none)
  */
  virtual double executeOperation(double lValue, double rValue, calc_error& err) {
    err.UpdateError(calc_error::EVAL_ERR, "'(' - is not an operator!");
    return -1;
  }
};

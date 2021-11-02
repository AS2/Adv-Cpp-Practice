#pragma once

#include <string>
#include <utility>

/**
@brief Calculator error class-singleton
*/
class calc_error {
private:
  /**
  * Default 'clac_error' constructor
  */
  calc_error() {};
public:
  /**
  * 'errorType_t' error types
  */
  typedef enum {
    NO_ERR = 0,

    SCANNER_ERR,
    PARSER_ERR,
    EVAL_ERR,

    OPER_ERR
  } errorType_t;

  errorType_t errorType;    ///< current error type
  std::string errorMessage; ///< current error message

  calc_error(const calc_error&) = delete;
  calc_error(calc_error&&) = delete;

  /**
  * Returns only existed 'calc_error' instance
  * @return calc_error reference
  */
  static calc_error& getInstance() {
    static calc_error err;
    return err;
  }

  /**
  * Update error status (copy semantic)
  * @param[in] _errorType - new error type
  * @param[in] _errorMessage - new error message
  */
  void UpdateError(errorType_t _errorType, const std::string& _errorMessage) {
    errorType = _errorType;
    errorMessage = _errorMessage;
  }

  /**
  * Update error status (move semantic)
  * @param[in] _errorType - new error type
  * @param[in] _errorMessage - new error message
  */
  void UpdateError(errorType_t _errorType, std::string&& _errorMessage) {
    errorType = _errorType;
    errorMessage = std::move(_errorMessage);
  }
};

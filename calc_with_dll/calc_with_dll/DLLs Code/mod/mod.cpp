#include "mod.h"
#include "../../operators/operator.h"

def_operator* defineOperator() {
  return new mod();
}
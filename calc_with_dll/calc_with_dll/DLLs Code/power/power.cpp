#include "power.h"
#include "../../operators/operator.h"

def_operator* defineOperator() {
  return new power();
}

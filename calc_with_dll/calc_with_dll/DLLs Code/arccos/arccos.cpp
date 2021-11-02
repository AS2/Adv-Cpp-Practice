#include "arccos.h"
#include "../../operators/operator.h"

/**
* Define arccos operator from dll
* @return def_operator pointer (arccos pointer)
*/
def_operator* defineOperator() {
  return new arccos();
}

#pragma once

#include "../operators/operator.h"

extern "C" {
  __declspec(dllexport) def_operator* defineOperator();
}
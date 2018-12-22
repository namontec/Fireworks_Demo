#include "pch.h"
#include "Tools.h"
#include <stdlib.h>


int Tools::random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

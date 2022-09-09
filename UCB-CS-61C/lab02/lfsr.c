#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void
lfsr_calculate (uint16_t *reg)
{
 /* YOUR CODE HERE */
 int bit = 0;
 if (*reg & 1)
  bit ^= 1;
 if (*reg & (1 << 2))
  bit ^= 1;
 if (*reg & (1 << 3))
  bit ^= 1;
 if (*reg & (1 << 5))
  bit ^= 1;
 *reg = *reg >> 1;

 if (bit)
  *reg |= (1 << 15);
}
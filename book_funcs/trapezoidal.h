#include <stdio.h>
#include <mpi.h>

float Trap(
          float  local_a   /* in */,
          float  local_b   /* in */,
          int    local_n   /* in */,
          float  h         /* in */);


float f(float x);
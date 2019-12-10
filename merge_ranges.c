#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "merge_ranges.h"

struct interval
{
  double start;
  double end;
};

int ascSort(const void* a, const void* b)
{
  return (*int(int* a) - *(int*)b );
};

double merge_ranges(){
  
  //sort array
  qsort(inArr, n, sizeof(double), ascSort);
  
  return merge_arr;
};

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "merge_ranges.h"
#include "structs_def.h"

//ascending order sort of array - from class notes
int ascSort (const void* a, const void* b) {
  return (*int(int* a) - *(int*)b );
};

double* merge_ranges (struct task inArr[], size_t n) {
  //sort array
  qsort(inArr.startT, n, sizeof(double), ascSort);
  
  //check for time overlaps
  double temp = 0.0;
  for (size_t i = 0; i < n; i++) {
    if (inArr[temp].endT >= inArr[i].startT) {
      inArr[temp].endT = max(inArr[temp].endT, inArr[i].endT);
      inArr[temp].startT = min(inArr[temp].startT, inArr[i].startT);
    }
    else {
      inArr[temp] = inArr[i];
      temp++;
    }
  }
  
  //create merge_arr
  double* merge_arr = malloc(sizeof(double) * temp);
 
  //fill merge_array with the overlapped intervals
  for (size_t i = 0; i < temp; i++) {
    merge_arr[i] = inArr[i].startT;
    merge_arr[i+1] = inArr[i].endT;
  }
  
  //free array memory
  free (inArr);
  
  return merge_arr;
}

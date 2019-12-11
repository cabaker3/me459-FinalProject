#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
//#include <stdbool.h>

#include "merge_ranges.h"
#include "structs.h"

int ascSort(const void* a, const void* b){
  return (*int(int* a) - *(int*)b );
};

//check to see if there is an overlap
//bool compareRange(Tasks t1, Tasks t2){
  //return (t1.startT < t2.startT);
//};

void merge_ranges(Tasks inArr[], size_t n){
  //create merge_arr
  
  //sort array
  qsort(inArr.startT, n, sizeof(double), ascSort);
  
  //check for time overlaps
  double temp = 0.0;
  for (size_t i = 0; i < n; i++){
    if (inArr[temp].endT >= inArr[i].startT){
      inArr[temp].endT = max(inArr[temp].endT, inArr[i].endT);
      inArr[temp].startT = max(inArr[temp].startT, inArr[i].startT);
    }
    else {
      inArr[temp] = inArr[i];
      temp++;
    }
  }
  
  //fill merge_array
  for (size_t i = 0; i < temp; i++){
    merge_arr[i].startT = inArr[i].startT;
    merge_arr[i].endT = inArr[i].endT;
  }
};

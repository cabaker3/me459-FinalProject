#include <math.h>
#include <stdlib.h>

#include "mamt.h"

#define HRS (24)

double mamt(double* arr, size_t n){
  //dynamically allocate arr
  double* arr2 = malloc(sizeof(float) * (n/2));
  double mamt;
  double mamt_sum = 0.0;
  
  for(size_t i = 0; i < n; i++){
    //calculate mamt (in hours)
    mamt = abs(arr[i] - arr[i+1])*HRS;
    arr2[i] = mamt;
  }
  
  for(size_t i = 0; i < (n/2); i++){
    mamt_sum += arr2[i];
  }
  
  free(arr);
  free(arr2);
  
  return mamt_sum;
}

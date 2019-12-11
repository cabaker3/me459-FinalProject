#include <math.h>
#include <stdlib.h>

#include "mamt.h"

#define HRS (24)

double mamt (double* arr, size_t n) {
  //dynamically allocate arr
  double* arr2 = malloc(sizeof(float) * (n/2));
  double mamt;
  double mamt_sum = 0.0;
  
  //loop through array to get task time
  for (size_t i = 0; i < n; i++) {
    //calculate mamt (in hours)
    mamt = abs(arr[i] - arr[i+1])*HRS;
    arr2[i] = mamt;
  }
  
  //apply business rules - see valid records
    //if mamt > 0 and < 16hrs, then 1 (count it as valid)
    //else > 16hrs or < 0hrs, then 0 (not valid)
  //sum valid records
  for (size_t i = 0; i < (n/2); i++) {
    if (arr2[i] >= 0 || arr2[i] <= 16) {
      mamt_sum += arr2[i];
    }
    else {
      mamt_sum += 0;
    }
  }
  
  free (arr);
  free (arr2);
  
  return mamt_sum;
}

#include <math.h>
#include <stdlib.h>

#include "mamt.h"
#include "structs.h"

#define HRS (24)

double* mamt(double* inArr, size_t n){
  //dynamically allocate arr
  double* arr = malloc(sizeof(float) * (n/2));
  double mamt;
  
  for(size_t i = 0; i < n; i++){
    //calculate mamt (in hours)
    mamt = abs(inArr[i] - inArr[i+1])*HRS;
    arr[i] = mamt;
  }
  
  return arr;
}

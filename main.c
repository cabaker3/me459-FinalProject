#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mamt.h"
#include "merge_ranges.h"
#include "structs_def.h"

int main(int argc, char* argv[]) {
  //read in data
  FILE *inFile, *outFile;
  
  inFile = fopen("task_data.csv","r");
  if (inFile == NULL) { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 
  
  char v;
  int temp = 0;
  for (v = getc(inFile); v != EOF; v = getc(inFile)) {
    if (v == '\n')  {
      temp += 1; 
    }
  }
  
  outFile = fopen("task_data_output.csv","w");
  if (outFile == NULL) { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 

  //create array to save task data
  struct task input[temp];
  size_t vals = 0;
  //save contents to array
  while (fscanf(inFile, "%d, %d", &input[vals].startT, &input[vals].endT) == 2)
    vals++;
  
  fclose (inFile); 
  
  //call merge range func
  double* arr = merge_ranges(input, sizeof(input)/sizeof(*input));
  
  //convert struct back to regular array
  //send merge range arr to mamt func
  double mamt_total = mamt(arr, vals);
  
  //write to csv
  //struct task output = {};
  
  //fwrite(&output, sizeof(struct task), 1, outFile); 
  
  fclose (outFile);
  
  free (arr);
  
  return 0;
}

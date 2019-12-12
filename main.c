#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mamt.h"
#include "merge_ranges.h"
#include "structs_def.h"

#define S2MS (1000)

int main(int argc, char* argv[]) {
  //read in data
  FILE *inFile, *outFile;
  
  //check to see if file can be opened
  inFile = fopen("task_data.csv","r");
  if (inFile == NULL) { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 
  
  //get the number of lines in the file for the size of the array
  char v;
  int temp = 0;
  for (v = getc(inFile); v != EOF; v = getc(inFile)) {
    if (v == '\n')  {
      temp += 1; 
    }
  }
  
  //opening the file to write
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
  
  //close input file
  fclose (inFile); 
  
  //call merge range func - get a new array of the time overlaps
  clock_t start = clock();
  double* arr = merge_ranges(input, sizeof(input)/sizeof(*input));
  clock_t end = clock();
  double time = ((double)(end - start)) / CLOCKS_PER_SEC * S2MS;
  
  //convert struct back to regular array
  //send merge range arr to mamt func - get the total task time
  clock_t start1 = clock();
  double mamt_total = mamt(arr, vals);
  clock_t end1 = clock();
  double time1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC * S2MS;
  
  //write to csv
  //struct task output = {};
  
  //fwrite(&output, sizeof(struct task), 1, outFile); 
  
  fclose (outFile);
  
  free (arr);
  
  return 0;
}

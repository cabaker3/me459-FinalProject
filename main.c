#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mamt.h"
#include "merge_ranges.h"

struct task
{
  //int id;
  double startT;
  double endT;
};

int main(int argc, char* argv[]) {
  //read in data
  FILE *inFile, *outFile;
  
  inFile = fopen("task_data","r");
  if (inFile == NULL) 
  { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 
  
  char v;
  int temp = 0;
  for (v = getc(inFile); v != EOF; v = getc(inFile)) 
    if (v == '\n')  
      temp += 1; 
  
  outFile = fopen("task_data_output","w");
  if (outFile == NULL) 
  { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 

  //create array to save task data
  struct task input[temp];
  size_t vals = 0;
  //save contents to array
  while(fscanf(inFile, "%d, %d", &input[vals].startT, &input[vals].endT) == 2))
    vals++;
  
  fclose(inFile); 
  
  //call merge range func
  
  //send merge range arr to mamt func
  
  //apply business rules - see valid records
    //if mamt > 0 and < 16hrs, then 1 (count it as valid)
    //else > 16hrs or < 0hrs, then 0 (not valid)
  //sum valid records
  
  //write to csv
  struct task output = {};
  
  fwrite(&output, sizeof(struct task), 1, outFile); 
  
  fclose(outFile);
  
  return 0;
}

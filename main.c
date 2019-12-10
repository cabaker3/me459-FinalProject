#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mamt.h"
#include "merge_ranges.h"

struct task
{
  int id;
  double startT;
  double endT;
};

int main(int argc, char* argv[]) {
  //create array to save task data
  
  //read in data
  FILE *inFile, *outFile;
  struct task input;
  
  inFile = fopen("task_data","r");
  if (inFile == NULL) 
  { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 
  
  outFile = fopen("task_data_output","w");
  if (outFile == NULL) 
  { 
    fprintf(stderr, "File can't be opened.\n"); 
    exit (1); 
  } 

  while(fread(&input, sizeof(struct task), 1, inFile)) 
    //save contents to array
  
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

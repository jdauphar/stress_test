#include "stdio.h"
#include "omp.h"
#include "time.h"
#include "stdlib.h"
#include "stdint.h"
// use 2^20 elements: a mega array 
#define ARRAY_LENGTH 1048576
// perform operations with number...
#define OPERAND 5
// number of threads to use
#define THREADS 5


void do_fun_stuff(){
  //printf("settin thread numbers");
  
  //fprintf(stderr,"\ngon do some fun stuff\n");
  uint64_t *array = malloc(sizeof(uint64_t) * ARRAY_LENGTH);
  //uint64_t *array[ARRAY_LENGTH];
  //fprintf(stderr,"\narray made\n");
  //printf("\narray[0] == %d\n",array[0]);
  //fprintf(stderr,"\nchanged 1 element\n");
  for(uint64_t i = 0; i < ARRAY_LENGTH - 1; i++){
    array[i] = rand() % 500; 
  }
  //printf("\ndid some fun stuff\n");
  
  {
    omp_set_num_threads(THREADS);
#pragma omp parallel for schedule(static, 4096*8)
    for(uint64_t i = 0; i < ARRAY_LENGTH - 1; i++){
      array[i] = array[i]*OPERAND;
      array[i] = array[i]/OPERAND;
      array[i] = array[i]-OPERAND;
      array[i] = array[i]*OPERAND;
      array[i] = array[i]/OPERAND;
      array[i] = array[i]+OPERAND;
      array[i] = array[i]-OPERAND;
      array[i] = array[i]*OPERAND;
      array[i] = array[i]/OPERAND;
    }
  }
}

void main(){

  srand(time(NULL));
  
  clock_t begin = clock();
  //#pragma omp parallel for schedule(static, 4096*8)
  //fprintf(stderr,"\nliterally havent even called for fun stuff\n");
  for(uint64_t i = 0; i < 500; i++)
    do_fun_stuff();  
  
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  //printf("\nIt took %f seconds to do the task\n",time_spent);
  printf("\n%f\n",time_spent);
}

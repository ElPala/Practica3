#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#define CYCLES 2000000000

int main(int argc, char const *argv[]) {

  int i;
  double leibniznumber=0;
  double sign = -1;
  long long start;
  long long finish;
  long long time;
  struct timeval ts;
  void fn(void *args);


  gettimeofday(&ts,NULL);
  start = ts.tv_sec;

int parArr[NTHREADS];
for(i=0;i<NTHREADS;i++)
{
  parArr[i]=i;
}


  void *pchild_stack = malloc(1024 * 1024);
  int pid = clone(fn, pchild_stack + (1024 * 1024),SIGCHLD, );


  printf("%f\n",leibniznumber );
  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;

  free(pchild_stack);


}

  void fn(void *args){

    int i=*((int *) args);
    double leibniznumber=*((double *) args);
    double sign=*((double *) args);

    for (i = 0; i < CYCLES; i++) {
      sign *= -1;
      leibniznumber+= sign/((2*i) + 1);
    }

}

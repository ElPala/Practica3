#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define CYCLES 2000000000

int main(int argc, char const *argv[]) {
  int i;
  double leibniznumber=0;
  double sign = -1;
  long long start;
  long long finish;
  long long time;
  struct timeval ts;
  
  gettimeofday(&ts,NULL);
  start = ts.tv_sec;

  for (i = 0; i < CYCLES; i++) {
    sign *= -1;
    leibniznumber+= sign/((2*i) + 1);
  }


  printf("%f\n",leibniznumber );
  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;
}

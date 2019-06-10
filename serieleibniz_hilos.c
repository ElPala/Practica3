#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define CYCLES 2000000000
#define NTHREADS 4
double leibniznumber=0;

void *tfunc(void *args)
{
  struct timeval t;
	int nthread=*((int *) args);
	int i;
	int inicio = nthread*(CYCLES/NTHREADS);
	int fin = (nthread + 1)*(CYCLES/NTHREADS);
  //printf("%d-%d\n", inicio, fin);
//  gettimeofday(&t, NULL);
//  printf("%ld\n", t.tv_sec );

  double sign;
  if(inicio % 2 == 0){
    sign=1;
  } else {
    sign=-1;
  }
  for (i = inicio; i < fin; i++) {
    leibniznumber+= sign/((2*i) + 1);
    sign *= -1;
  }
  //gettimeofday(&t, NULL);
//  printf("%ld\n", t.tv_sec );

}

int main(int argc, char const *argv[]) {

  long long start;
  long long finish;
  long long time;
  struct timeval ts;
  int i;
  int parArr[NTHREADS];
	pthread_t tid[NTHREADS];
  gettimeofday(&ts,NULL);
  start = ts.tv_sec;

  for(i=0;i<NTHREADS;i++)
	{
		parArr[i]=i;
		pthread_create(&tid[i],NULL,tfunc,(void *) &parArr[i]);
	}

	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);

  printf("%f\n",leibniznumber );

  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;
}

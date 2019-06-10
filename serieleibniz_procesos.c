#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/shm.h>
void proc(int n,int id );

#define CYCLES 2000000000
#define NPROCS 4

int main(int argc, char const *argv[]) {
  pid_t p;
  int status;
  int id;
  int i;
  double *  pleibniznumber;
  long long start;
  long long finish;
  long long time;
  struct timeval ts;
  gettimeofday(&ts,NULL);
  start = ts.tv_sec;
  id = shmget(IPC_PRIVATE, sizeof(double),IPC_CREAT | 0666 );
  if(id<0){
    exit(1);
  }

  for ( i = 0; i < NPROCS; i++) {
    p=fork();
  	if(p==0){
      proc(i, id);
    }
  }

  for ( i = 0; i < NPROCS; i++)
      wait(&status);
  pleibniznumber = (double*) shmat(id, NULL, 0);
  if (pleibniznumber == (void *) -1) {
    exit(1);
  }

  printf("%f\n", *pleibniznumber );
  if (shmdt(pleibniznumber) == -1)
      exit(1);

  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;
}

void proc(int n, int id )
{
  int inicio;
	int fin;
  int j;
  double sign;
  double*  pleibniznumber;
  pleibniznumber = (double*)shmat(id, NULL, 0);
  if (pleibniznumber == (void *) -1) {
    exit(1);
  }
  inicio = n*(CYCLES/NPROCS);
  fin = (n + 1)*(CYCLES/NPROCS);
  if(inicio % 2 == 0){
    sign=1;
  } else {
    sign=-1;
  }
  printf("soy hijo %d %d-%d\n", getpid(),inicio, fin );
  for (j = inicio; j < fin; j++) {
    (*pleibniznumber)+= sign/((2*n) + 1);
    sign *= -1;
  }

  if (shmdt(pleibniznumber) == -1){
      exit(1);
  }
  else{
    exit;
  }
}

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
  int key;
  int i;
  double *  pleibniznumber;
  long long start;
  long long finish;
  long long time;
  struct timeval ts;
  gettimeofday(&ts,NULL);
  start = ts.tv_sec;
  key = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT | 0666);
  if(key<0){
    printf("Erron en la creación de la memoria compartida\n");
    exit(1);
  }
//printf("%d %d 1\n",id, getpid());
  for ( i = 0; i < NPROCS; i++) {
    p=fork();
  	if(p==0){
      proc(i, key);
      exit(0);
    }
  }

  for ( i = 0; i < NPROCS; i++)
      wait(&status);
  //printf("%d %d 3\n",id, getpid());
  pleibniznumber = (double*) shmat(key, NULL, 0);
  if (pleibniznumber == (void *) -1) {
    printf("Erron en ABRIR puntero 1 %d\n",getpid());
    exit(1);
  }
  printf("%f\n", *pleibniznumber );

  if (shmdt(pleibniznumber) == -1){
    printf("Erron en CERRAR puntero 1 %d\n",getpid());
        exit(1);
  }
  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;
}

void proc(int n, int key )
{
  int inicio;
	int fin;
  int j;
  double sign;
  double*  pleibniznumber;
  //printf("%d %d 2\n",id, getpid());
  pleibniznumber = (double*)shmat(key, NULL, 0);
  if (pleibniznumber == (void *) -1) {
    printf("Erron en ABRIR puntero 0 %d\n",getpid());
    exit(1);
  }
  inicio = n*(CYCLES/NPROCS);
  fin = (n + 1)*(CYCLES/NPROCS);
  if(inicio % 2 == 0){
    sign=1;
  } else {
    sign=-1;
  }

  //printf("numero- %f %d 1\n", *pleibniznumber , getpid());
  //printf("soy hijo %d %d-%d\n", getpid(),inicio, fin );
  for (j = inicio; j < fin; j++) {
    (*pleibniznumber)+= sign/((2*j) + 1);
    sign *= -1;
  }
  //printf("numero:%f %d 2\n", *pleibniznumber , getpid());
  if (shmdt(pleibniznumber) == -1)
      printf("Erron en CERRAR puntero 0 %d\n",getpid());
      exit(1);
}

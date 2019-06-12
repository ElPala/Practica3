#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#define _GNU_SOURCE
#define CYCLES 2000000000

int main(int argc, char const *argv[]) {
  //int clone(int (*pfn)(void), void *, int ,int,double,double);
  int i;
  double leibniznumber=0;
  double sign = -1;
  long long start;
  long long finish;
  long long time;
  struct timeval ts;

  //void fn(int, double, double);

  const int STACK_SIZE = 65536;
  char* stack = malloc(STACK_SIZE);
  if (!stack) {
    perror("malloc");
      exit(1);
      }

  unsigned long flags = 0;
  if (argc > 1 && !strcmp(argv[1], "vm")) {
        flags |= CLONE_VM;
       }

   char buf[100];
   strcpy(buf, "hello from parent");
   if (clone(child_func, stack + STACK_SIZE,
     flags | SIGCHLD, buf) == -1) {
      perror("clone");
          exit(1);
        }

  int status;
  if (wait(&status) == -1) {
        perror("wait");
            exit(1);
          }
           printf("Child exited with status %d. buf =\"%s\"\n", status, buf);
            return 0;
          }


  gettimeofday(&ts,NULL);
  start = ts.tv_sec;

  //void *pchild_stack = malloc(1024 * 1024);
  //int pid = clone(fn, pchild_stack + (1024 * 1024),SIGCHLD,i, leibniznumber,sign );
  //fn(i, leibniznumber, sign);

  printf("%f\n",leibniznumber );
  gettimeofday(&ts,NULL);
  finish = ts.tv_sec;
  time = finish-start;
  printf("Tiempo total: %d seg\n",(int) time );
  return 0;
}

  void fn(int i, double leibniznumber, double sign){
    printf("si lleguew");

    for (i = 0; i < CYCLES; i++) {
      sign *= -1;
      leibniznumber+= sign/((2*i) + 1);
    }
}

static int child_func(void* arg) {
  char* buf = (char*)arg;
  printf("Child sees buf = \"%s\"\n", buf);
 strcpy(buf, "hello from child");
 return 0;
}

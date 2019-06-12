#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#define _GNU_SOURCE

static int child_func(void* arg) {
  char* buf = (char*)arg;
  printf("Child sees buf = \"%s\"\n", buf);
 strcpy(buf, "hello from child");
 return 0;
}

int main(int argc, char** argv) {
  // Allocate stack for child task.
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
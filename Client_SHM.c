#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct memory {
  char buff[100];
  int status, pid1, pid2;
};

struct memory *shmptr;

void receive(int signum) {
  if (signum == SIGUSR2) {
    printf("Received From Server: ");
    puts(shmptr->buff);
  }
}

int main() {
  int pid = getpid();
  int shmid = shmget(111, sizeof(struct memory), IPC_CREAT | 0666);
  shmptr = (struct memory *)shmat(shmid, NULL, 0);
  shmptr->pid2 = pid;
  shmptr->status = -1;
  signal(SIGUSR2, receive);
  printf("Start messaging: \n");
  while (1) {
    char* re = fgets(shmptr->buff, 100, stdin);
    shmptr->status = 1;
    kill(shmptr->pid1, SIGUSR1);
  }
  shmdt((void *)shmptr);
  return 0;
}
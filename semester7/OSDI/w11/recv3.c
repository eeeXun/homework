// receiver
#include "bundbuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

int main() {
  int msqid;
  key_t key = 0x1234;
  int msgflg = IPC_CREAT | 0666;
  int ret;
  struct msgbuf mbuf;

  msqid = msgget(key, msgflg);

  while (1) {
    msgrcv(msqid, &mbuf, sizeof(mbuf.mtext), 0, 0);
    if (strcmp(mbuf.mtext, "exit\n") == 0) {
      printf("Recv exit\n");
      msgctl(msqid, IPC_RMID, NULL);
      exit(0);
    } else {
      printf("Received message: %s", mbuf.mtext);
    }
  }

  return 0;
}

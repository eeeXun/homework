// receiver
#include "msgbuf.h"
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

  for (int i = 0; i < 3; i++) {
    msgrcv(msqid, &mbuf, sizeof(mbuf.mtext), 0, 0);
    printf("Received message: %s\n", mbuf.mtext);
  }

  return 0;
}

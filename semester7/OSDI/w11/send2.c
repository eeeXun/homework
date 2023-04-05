// sender
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
  printf("Sender message queue id: %d\n", msqid);

  mbuf.mtype = 5;
  while (1) {
    fgets(mbuf.mtext, MSGSIZE, stdin);
    if (strcmp(mbuf.mtext, "\n") != 0) {
      msgsnd(msqid, &mbuf, sizeof(mbuf.mtext), 0);
    }
    if (strcmp(mbuf.mtext, "exit\n") == 0) {
      printf("Send exit\n");
      break;
    }
  }

  return 0;
}

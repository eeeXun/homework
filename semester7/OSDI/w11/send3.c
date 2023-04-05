// sender
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
  struct msqid_ds ds;

  msqid = msgget(key, msgflg);
  printf("Sender message queue id: %d\n", msqid);
  msgctl(msqid, IPC_STAT, &ds);
  ds.msg_qbytes = MSGSIZE * MSGNUM;
  msgctl(msqid, IPC_SET, &ds);

  mbuf.mtype = 5;
  while (1) {
    fgets(mbuf.mtext, MSGSIZE, stdin);
    if (strcmp(mbuf.mtext, "\n") != 0) {
      ret = msgsnd(msqid, &mbuf, sizeof(mbuf.mtext), 0);
      if (ret == 0) {
        printf("Send success\n");
      }
    }
    if (strcmp(mbuf.mtext, "exit\n") == 0) {
      printf("Send exit\n");
      break;
    }
  }

  return 0;
}

#define MSGSIZE 100

struct msgbuf {
  long mtype;
  char mtext[MSGSIZE];
};

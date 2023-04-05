#define MSGSIZE 100
#define MSGNUM 5

struct msgbuf {
  long mtype;
  char mtext[MSGSIZE];
};

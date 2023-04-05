#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "Branko:$ "
#define TOKENSTR " \n"
#define ARGSIZE 10

int main() {
  int buf_size = 100;
  char *buf = (char *)malloc(buf_size * sizeof(char));
  char *token;
  int token_index;
  char *arg[ARGSIZE];
  pid_t pid;

  printf("A simplified shell ... Enter exit to terminate!\n");
  while (1) {
    token_index = 0;
    printf(PROMPT);
    buf = (char *)malloc(buf_size * sizeof(char));
    getline(&buf, &buf_size, stdin);
    if (strcmp(buf, "\n") == 0) {
      continue;
    }
    token = strtok(buf, TOKENSTR);
    arg[token_index] = token;
    token_index++;
    while (token != NULL) {
      token = strtok(NULL, TOKENSTR);
      arg[token_index] = token;
      token_index++;
    }
    if (strcmp(arg[0], "exit") == 0) {
      printf(PROMPT "Simplified shell terminated!\n");
      break;
    }

    pid = fork();
    if (pid == 0) { // child
      if (execvp(arg[0], arg)) {
        printf("Error Commend!\n");
        exit(1);
      }
    } else { // parent
      wait(NULL);
    }
  }
}

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(argc==3){
  int fp = open(argv[2], O_RDONLY | O_CREAT, S_IRWXU);
  char buf[4096];
  int n = read(fp, buf, 4096);
  int poss = 0;
  int next = 0;
  int count = 0;
  for (int i = 0; i < n - strlen(argv[1])+1; i++) {
    for (int j = 0; j < strlen(argv[1]); j++) {
      if(buf[i+j]=='\n'){
        next=i+j+1;
      }
      if (buf[i + j] == argv[1][j]) {
        poss = 1;
      } else {
        poss = 0;
        break;
      }
      if (buf[i + j] == argv[1][strlen(argv[1])-1]) {
        if (poss == 1) {
          for (int k = next; buf[k]!='\n'; k++) {
            printf("%c", buf[k]);
          }
          printf("\n");
          count++;
        }
        next = i + j + 1;
      }


    }
  }
  printf("Count of values: %d\n",count);
  int sp = close(fp);
  }
  else if(argc==4){
    if(strcmp(argv[1],"-c")==0){
    int fp = open(argv[3], O_RDONLY | O_CREAT, S_IRWXU);
    char buf[4096];
    int n = read(fp, buf, 4096);
    int poss = 0;
    int next = 0;
    int count = 0;
    for (int i = 0; i < n - strlen(argv[2])+1; i++) {
      for (int j = 0; j < strlen(argv[2]); j++) {
        if(buf[i+j]=='\n'){
          next=i+j+1;
        }
        if (buf[i + j] == argv[2][j]) {
          poss = 1;
        } else {
          poss = 0;
          break;
        }
        if (buf[i + j] == argv[2][strlen(argv[2])-1]) {
          if (poss == 1) {
            for (int k = next; buf[k]!='\n'; k++) {
              printf("%c", buf[k]);
            }
            printf("\n");
          }
          next = i + j + 1;
        }
      }
    }
    int sp = close(fp);
    }
      else if(strcmp(argv[1],"-v")==0){
        int fp = open(argv[3], O_RDONLY | O_CREAT, S_IRWXU);
        char buf[4096];
        int n = read(fp, buf, 4096);
        int poss = 0;
        int next = 0;
        int spos=0;
        int fsos=0;
        int count = 0;
        for (int i = 0; i < n - strlen(argv[2])+1; i++) {
          for (int j = 0; j < strlen(argv[2]); j++) {
            if (buf[i + j] == argv[2][j]) {
              poss = 1;
              spos=1;

            } else {
              poss = 0;
              spos=0;
              break;
            }
          }
          if(spos==1){
            fsos=1;
              }
          //printf("%d%c",next,buf[i]);
          if (poss == 0 && buf[i]=='\n'&&fsos==0) {
            for (int k = next; buf[k]!='\n'; k++) {
              printf("%c", buf[k]);
            }
            printf("\n");
          }
          if(buf[i]=='\n'){fsos=0;next=i+1;}
        }
        if (poss == 0 && fsos==0) {
          for (int k = next; buf[k]!='\n'; k++) {
            printf("%c", buf[k]);
          }
          printf("\n");
        }
        int sp = close(fp);
        }
    else if(strcmp(argv[1],"-n")==0){
      int fp = open(argv[3], O_RDONLY | O_CREAT, S_IRWXU);
      char buf[4096];
      int n = read(fp, buf, 4096);
      int poss = 0;
      int next = 0;
      int count = 0;
      for (int i = 0; i < n - strlen(argv[2])+1; i++) {
        for (int j = 0; j < strlen(argv[2]); j++) {
          if(buf[i+j]=='\n'){
            next=i+j+1;
          }
          if (buf[i + j] == argv[2][j]) {
            poss = 1;
          } else {
            poss = 0;
            break;
          }
          if (buf[i + j] == argv[2][strlen(argv[2])-1]) {
            if (poss == 1) {
              count++;
            }
            next = i + j + 1;
          }


        }
      }
      printf("Count of values: %d\n",count);
      int sp = close(fp);
    }
  }
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    if (argc == 4) {
      char c;
      if (strcmp(argv[1], "-i") == 0) {
printf("Do you want to overwrite the file %s?(y/n): ",argv[2]);
int s = scanf("%c",&c);
      }
      if (c == 'y') {
        char *buf = (char *)malloc(100 * sizeof(char));
        int fp = open(argv[2], O_RDONLY | O_CREAT, S_IRWXU);
        int rd = read(fp, buf, 100);
        if (rd != -1 | fp != -1) {
          int wr = open(argv[3], O_WRONLY | O_CREAT, S_IRWXU);
          int wri = write(wr, buf, rd);
          if (wr == -1 | wri == -1) {
            printf("Error writing file\n");
          } else {
            printf("Copied Successfully\n");
          }
          int cl = close(fp);
          int mp = close(wr);
        } else {
          printf("Error creating file\n");
        }
      }
    } else {
      printf("Invalid number of arguments\n");
    }
  } else {
    char *buf = (char *)malloc(100 * sizeof(char));
    int fp = open(argv[1], O_RDONLY | O_CREAT, S_IRWXU);
    int rd = read(fp, buf, 100);
    if (rd != -1 | fp != -1) {
      int wr = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
      int wri = write(wr, buf, rd);
      if (wr == -1 | wri == -1) {
        printf("Error writing file\n");
      } else {
        printf("Copied Successfully\n");
      }
      int cl = close(fp);
      int mp = close(wr);
    } else {
      printf("Error creating file\n");
    }
  }
}

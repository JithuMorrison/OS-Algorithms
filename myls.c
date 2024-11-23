#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int isDir(const char *fileName) {
  struct stat path;
  stat(fileName, &path);
  return S_ISDIR(path.st_mode);
}
void perm(struct stat fileStat) {
  printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
printf(" %ld ", fileStat.st_size);
printf(" %ld ", fileStat.st_mtime);
printf(" %ld ", fileStat.st_dev);
printf(" %ld ", fileStat.st_ino);
}
void recur(char *name) {
  DIR *dr;
  struct dirent *en;
  dr = opendir(name);
  if (dr) {
    while ((en = readdir(dr)) != NULL) {
      if (en->d_name[0] != '.') {
        printf("%s\n", en->d_name);
        if (isDir(en->d_name) == 1) {
          recur(en->d_name);
        }
      }
    }
  }
  closedir(dr);
}
int main(int argc, char *argv[]) {
  if (argc == 1) {
    DIR *dr;
    struct dirent *en;
    dr = opendir(".");
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if (en->d_name[0] != '.') {
          printf("%s\n", en->d_name);
        }
      }
      closedir(dr);
    }
  } else {
    if (strcmp(argv[1], "-R") == 0) {
      recur(argv[2]);
    } else if (strcmp(argv[1], "-l") == 0) {
      struct stat fs;
      DIR *dr;
      int r;
      struct dirent *en;
      dr = opendir(argv[2]);
      if (dr) {
        while ((en = readdir(dr)) != NULL) {
          if (en->d_name[0] != '.') {
            r = stat(en->d_name, &fs);
            if (r == -1) {
fprintf(stderr,"File error\n");
            } else {
              perm(fs);
            }
            printf("%s\n", en->d_name);
          }
        }
      }
      closedir(dr);
    } else {
      DIR *dr;
      struct dirent *en;
      dr = opendir(argv[1]);
      if (dr) {
        while ((en = readdir(dr)) != NULL) {
          if (en->d_name[0] != '.') {
            printf("%s\n", en->d_name);
          }
        }
      }
      closedir(dr);
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct dir {
    int id;
    char name[20];
    struct dir *parent;
    struct dir *child[100];
    int child_count;
    struct file *file[100];
    int file_count;
};

struct sidir {
    int id;
    char name[20];
    int file_count;
    struct file *file[100];
};

struct file{
    int id;
    char name[20];
    char perm[20];
};

void single(struct sidir *sroot){
    sroot->id = 1;
    int numt=0;
  while (numt != 3) {
    printf("\n\n1. Create a file\n2. Display address table\n3.Navigate to directory\n4. Create a sub-directory\n5. Exit\nEnter your choice: ");
     scanf("%d",&numt);
   switch(numt)
   {
      case 1:
        sroot->file_count+=1;
        sroot->file[sroot->file_count-1] = (struct file *)malloc(sizeof(struct file));
        printf("Enter the name of the file: ");
        scanf("%s",sroot->file[sroot->file_count-1]->name);
        printf("Enter the permission of the file: ");
        scanf("%s",sroot->file[sroot->file_count-1]->perm);
        sroot->file[sroot->file_count-1]->id = 100+sroot->file_count+sroot->file_count*45+sroot->file_count*sroot->file_count*sroot->file_count+sroot->file_count*13;
        break;
      case 2:
        for(int i=0;i<sroot->file_count;i++){
          printf("\nFile id %d: %s\tPermission: %s",sroot->file[i]->id,sroot->file[i]->name,sroot->file[i]->perm);
        }
        break;
      case 3:
        printf("Exiting directory.\n");
        break;
      default:
        printf("Enter a valid option.\n");
   }
  }
}

int main() {
  int opt = 1;
  char nam[20];
  struct dir *root = (struct dir *)malloc(sizeof(struct dir));
  struct sidir *sroot = (struct sidir *)malloc(sizeof(struct sidir));
  while (opt != 3) {
 printf("\nFile Organization Methods:\n1. Single-level Directory\n2. Tree-structured Directory\n3. Exit\nEnter your choice:");
 scanf("%d",&opt);
 switch(opt)
 {
    case 1:
      scanf("%s",nam);
      strcpy(sroot->name, nam);
      single(sroot);
      break;
    case 2:
      break;
    case 3:
      printf("Exiting program.\n");
      break;
    default:
      printf("Enter a valid option.\n");
 }
  }
}
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int final_num; 
    struct Node* next;
    struct Node* prev;
};

void insertAtBeginning(struct Node** head, int data, int final_num) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->final_num = final_num; 
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtEnd(struct Node** head, int data, int final_num) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->final_num = final_num; 
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("(%d, %d) -> ", current->data, current->final_num);
        current = current->next;
    }
    printf("NULL\n");
}

void printlis(struct Node* head,int totsize) {
    struct Node* current = head;
    while (current->next != NULL) {
        printf("(%d, %d, %d) -> ", current->data, current->final_num,(current->next->final_num)-(current->final_num));
        current = current->next;
    }
  printf("(%d, %d, %d) -> NULL\n", current->data, current->final_num,totsize-(current->final_num));
}

void colase(struct Node* head,int totsize){
    struct Node* current = head;
    while (current->next!= NULL) {
        while(current->next->next!=NULL && current->data==0 && current->next->data==0 ){
            current->next=current->next->next;
            current->next->prev=current;
        }
            if(current->next->next==NULL && current->data==0 && current->next->data==0){
                current->next=NULL;
            }
        else{
            current = current->next;  
        }
    }
}

void delet(struct Node* head,int addrex){
    struct Node* current = head;
    while (current != NULL) {
        if(current->data==addrex){
            current->data=0;
        }
        current = current->next;
    }
}

int isMemoryAvailable(struct Node* head, int pg, int size,int finalsize) {
    struct Node* current = head;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    while (current != NULL) {
      if(current->next!=NULL){
        if (current->data == 0 && size < (current->next != NULL ? current->next->final_num - current->final_num : 0)) {
            current->data=pg;
            newNode->next=current->next;
            newNode->prev=current;
            current->next=newNode;
            newNode->next->prev=newNode;
            newNode->data=0;
            newNode->final_num=current->final_num+size;
            return 1;
        }
      else if (current->data == 0 && size == (current->next != NULL ? current->next->final_num - current->final_num : 0)){
        current->data=pg;
        return 1;
      }
    }
      else{
        if(current->data == 0 && size < (current != NULL ? finalsize - current->final_num : 0)){
          
          current->data=pg;
          newNode->next=current->next;
          newNode->prev=current;
          current->next=newNode;
          newNode->data=0;
          newNode->final_num=current->final_num+size;
          return 1;
        }
        else if(current->data == 0 && size == (current != NULL ? finalsize - current->final_num : 0)){
          current->data=pg;
          return 1;
        }
      }
        current = current->next;
    }
    return 0;
}

int main(void) {
    struct Node* memory = NULL;
    int totalsize = 135;

    insertAtEnd(&memory, 0, 110);
    insertAtEnd(&memory, 0, 112);
    insertAtEnd(&memory, 0, 117);
    insertAtEnd(&memory, 0, 120);
    insertAtEnd(&memory, 0, 125);

    int size;
    int k = 1;
    int pg;
    int col=0;
    int del=0;
    printlis(memory,totalsize);
    while (k) {
        printf("Do you want to scan?: ");
        int o = scanf("%d", &k);
        if (k == 1) {
            printf("Enter the size: ");
            o = scanf("%d", &size);
            printf("Enter page no: ");
            o = scanf("%d", &pg);
            if (isMemoryAvailable(memory,pg,size,totalsize)) {
              
                printf("Memory available\n");
            } else {
                printf("Memory not available\n");
            }
          printlis(memory,totalsize);
            printf("want to delete?: ");
            o = scanf("%d", &del);
            if(del==1){
                int id;
                o = scanf("%d", &id);
                delet(memory, id);
                printlis(memory,totalsize);
            }
            printf("want to colase?: ");
            o = scanf("%d", &col);
            if(col==1){
                colase(memory, totalsize);
                printlis(memory,totalsize);
            }
        }
    }

    struct Node* temp;
    while (memory != NULL) {
        temp = memory;
        memory = memory->next;
        free(temp);
    }

    return 0;
}

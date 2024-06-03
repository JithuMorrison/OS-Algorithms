#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    int final_num; 
    int free;
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
    newNode->final_num = final_num; // Initialize final_num
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
    newNode->final_num = final_num; // Initialize final_num
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

int isAvailable(struct Node* head,int siz){
    if(head->free<siz){
        return 0;
    }
    return 1;
}

void delet(struct Node* head,int addrex){
    struct Node* current = head;
    int vadd=1;
    while (current != NULL) {
        if(vadd==addrex && current->data!=0){
            current->data=0;
            head->free++;
        }
        vadd++;
        current = current->next;
    }
}

int getlen(struct Node* head) {
    int length = 0;
    struct Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

struct Node* getnod(struct Node* head, int index) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    return current;
}

int contiguous(struct Node* start, int total) {
    struct Node* current = start;
    int free_count = 0;
    while (current != NULL && free_count < total) {
        if (current->data != 0) {
            return 0; // Not enough contiguous free nodes
        }
        current = current->next;
        free_count++;
    }
    return free_count == total;
}

void insrtpg(struct Node* start, int total, int pg, struct Node* head) {
    struct Node* current = start;
    for (int i = 0; i < total; i++) {
        current->data = pg;
        head->free--;
        current = current->next;
    }
}

void check(struct Node* head, int curre, int total, int pg) {
    int length = getlen(head);
    if (total > length) {
        printf("Not enough nodes to insert\n");
        return;
    }

    srand(time(NULL));
    int startind = rand() % length;

    struct Node* start = getnod(head, startind);

    if (contiguous(start, total)) {
        insrtpg(start, total, pg, head);
        printf("Inserted\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        if (contiguous(current, total)) {
            insrtpg(current, total, pg, head);
            printf("Inserted\n");
            return;
        }
        current = current->next;
    }

    printf("Memory not available\n");
}

int main(){
    struct Node* memory = NULL;
    int totalsize = 10;
    // Initialize memory blocks
    for(int i=0;i<totalsize;i++){
        insertAtEnd(&memory, 0, i);
    }
    memory->free = totalsize;
    printList(memory);
    int size;
    int k = 1;
    int pg;
    int del=0;
    while (k) {
        printf("Do you want to scan?: ");
        int o = scanf("%d", &k);
        if (k == 1) {
            printf("Enter the size: ");
            o = scanf("%d", &size);
            printf("Enter file no: ");
            o = scanf("%d", &pg);
            if (isAvailable(memory,size)) {
                check(memory, size%totalsize,size,pg);
                printList(memory);
            } else {
                printf("Memory not available\n");
            }
            printf("want to delete?: ");
            o = scanf("%d", &del);
            if(del==1){
                int id;
                o = scanf("%d", &id);
                delet(memory, id);
                printList(memory);
            }
        }
    }
}

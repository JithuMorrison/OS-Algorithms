#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    int final_num; 
    int free;
    struct Node* prevlink;
    struct Node* nextlink;
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

void printLink(struct Node* head,int id) {
    struct Node* current = head;
    struct Node* murrent;
    struct Node* turrent;
    while (current != NULL) {
        if(current->data==id){
        murrent=current;
        turrent=current->prevlink;
        while (murrent != NULL) {
            printf("(%d, %d) -> ", murrent->data, murrent->final_num);
            murrent = murrent->nextlink;
            }
        while (turrent != NULL) {
            printf("(%d, %d) -> ", turrent->data, turrent->final_num);
            turrent = turrent->prevlink;
            }
            current=NULL;
        }
        else{
        current = current->next;
        }
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

void check(struct Node* head, int curre, int total, int pg) {
    int length = getlen(head);
    srand(time(NULL));
    int startindx = rand() % length;
    struct Node* current = getnod(head, startindx);
    struct Node* nest = NULL;

    while (current != NULL && total > 0) {
        if (current->data == 0) {
            current->data = pg;
            head->free--;
            total--;

            if (nest != NULL) {
                nest->nextlink = current;
                current->prevlink = nest;
            }
            nest = current;
        }
        current = current->next;
    }

    if (total > 0) {
        current = head;
        while (current != NULL && total > 0) {
            if (current->data == 0) {
                current->data = pg;
                head->free--;
                total--;

                if (nest != NULL) {
                    nest->nextlink = current;
                    current->prevlink = nest;
                }
                nest = current;
            }
            current = current->next;
        }
    }
    nest->nextlink = NULL;
    printf("Inserted\n");
}

int main(){
    struct Node* memory = NULL;
    int totalsize = 10;
    for(int i=0;i<totalsize;i++){
        insertAtEnd(&memory, 0, i);
    }
    memory->free = totalsize;
    printList(memory);
    int size;
    int k = 1;
    int pg;
    int col=0;
    int del=0;
    while (k) {
        printf("Do you want to scan?: ");
        int o = scanf("%d", &k);
        if (k == 1) {
            printf("Enter the size: ");
            o = scanf("%d", &size);
            printf("Enter file no: ");
            o = scanf("%d", &pg);
            if (memory->free>=size) {

                printf("Memory available\n");
                check(memory, size%totalsize,size,pg);
                printList(memory);
            } else {
                printf("Memory not available\n");
            }
            printf("want to delete?: ");
            o = scanf("%d", &del);
            if(del==1){
                int id;
                printf("Index to delete: ");
                o = scanf("%d", &id);
                delet(memory, id);
                printList(memory);
            }
            printf("want to find link?: ");
            o = scanf("%d", &col);
            if(col==1){
                int id;
                printf("Index to link: ");
                o = scanf("%d", &id);
                printLink(memory, id);
            }
        }
    }
}

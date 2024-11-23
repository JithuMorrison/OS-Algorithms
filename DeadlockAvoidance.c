#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int n_re = 3;
int n_pr = 5;

int max[5][3] = {
{7, 5, 3},
{3, 2, 2}, 
{9, 0, 2},
{2, 2, 2}, 
{4, 3, 3}};

int alloc[5][3] = {
{0, 1, 0}, 
{2, 0, 0}, 
{3, 0, 2}, 
{2, 1, 1}, 
{0, 0, 2}};

int need[5][3] = {
{7, 4, 3}, 
{1, 2, 2}, 
{6, 0, 0}, 
{0, 1, 1}, 
{4, 3, 1}};

int avail[3] = {3, 3, 2};
bool finished[5];

bool isSafe(int process, int work[]) {
  for (int i = 0; i < n_re; i++) {
    if (need[process][i] > work[i]) {
      return false;
    }
  }
  return true;
}

bool isSafe1(int process,int neednew[][100], int work[]) {
  for (int i = 0; i < n_re; i++) {
    if (neednew[process][i] > work[i]) {
      return false;
    }
  }
  return true;
}

void safetySequence() {
  int work[100];
  for (int i = 0; i < n_re; i++) {
    work[i] = avail[i];
  }

  bool found;
  int safeSequence[100];
  int count = 0;

  while (count < n_pr) {
    found = false;
    for (int i = 0; i < n_pr; i++) {
      if (!finished[i] && isSafe(i, work)) {
        for (int j = 0; j < n_re; j++) {
          work[j] += alloc[i][j];
        }
        safeSequence[count++] = i;
        finished[i] = true;
        found = true;
      }
    }
    if (!found) {
      printf("Unsafe State: System cannot complete all processes!\n");
      return;
    }
  }

  printf("Safe Sequence: ");
  for (int i = 0; i < n_pr; i++) {
    printf("P%d ", safeSequence[i]);
  }
  printf("\n");
}

void processRequest() {
  int process;
  printf("Enter process number: ");
  int fu = scanf("%d", &process);

  int request[100];
  printf("Enter resource request for process P%d ( %d resources seperated by spaces ): ", process ,n_re);
  for (int i = 0; i < n_re; i++) {
    int fu = scanf("%d", &request[i]);
  }

  int temp_avail[100];
  int temp_alloc[100][100];
  int temp_need[100][100];
  printf("Available: ");
  for (int i = 0; i < n_re; i++) {
    temp_avail[i] = avail[i] - request[i];
    printf("%d ", temp_avail[i]);
  }
  printf("\nNeed matrix:");
  for (int i = 0; i < n_pr; i++) {
    printf("\n");
    for (int j = 0; j < n_re; j++) {
      temp_alloc[i][j] = alloc[i][j];
      temp_need[i][j] = need[i][j];
      if (i != process) {
        printf("%d ", temp_need[i][j]);
      }
    }
    if (i == process) {
      for (int j = 0; j < n_re; j++) {
        temp_alloc[i][j] += request[j];
        temp_need[i][j] -= request[j];
        printf("%d ", temp_need[i][j]);
      }
    }
  }
  printf("\n");

  bool safe = false;
  bool temp_finished[100] = {false};
  int work[100];
  for (int i = 0; i < n_re; i++) {
    work[i] = temp_avail[i];
  }

  int safeSequence[100];
  int count = 0;

  while (count < n_pr) {
    safe = false;
    for (int i = 0; i < n_pr; i++) {
      if (!temp_finished[i] && isSafe1(i,temp_need, work)) {
        for (int j = 0; j < n_re; j++) {
          work[j] += temp_alloc[i][j];
        }

        safeSequence[count++] = i;
        temp_finished[i] = true;
        safe = true;
      }
    }

    if (!safe) {
      break;
    }
  }

  if (count == n_pr) {
    printf("Request granted.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < n_pr; i++) {
      printf("P%d ", safeSequence[i]);
    }
    printf("\n");
  } else {
    printf("Request denied. Process must wait.\n");
  }
}

void printData() {
  printf("Allocation Matrix:\n");
  for (int i = 0; i < n_pr; i++) {
    for (int j = 0; j < n_re; j++) {
      printf("%d ", alloc[i][j]);
    }
    printf("\n");
  }

  printf("Max Matrix:\n");
  for (int i = 0; i < n_pr; i++) {
    for (int j = 0; j < n_re; j++) {
      printf("%d ", max[i][j]);
    }
    printf("\n");
  }

  printf("Need Matrix:\n");
  for (int i = 0; i < n_pr; i++) {
    for (int j = 0; j < n_re; j++) {
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }

  printf("Available Resources:\n");
  for (int i = 0; i < n_re; i++) {
    printf("%d ", avail[i]);
  }
  printf("\n");
}
int main() {
  int choice;
  printf("1. Read Data\n");
  printf("2. Print Data\n");
  printf("3. Safety Sequence\n");
  printf("4. Process Request\n");
  printf("5. Exit\n");

  printf("Enter your choice(1-5): ");
  int fu = scanf("%d", &choice);
  while (1) {
    switch (choice) {
    case 1:
      printf("Alloc matrix:\n");
      for (int i = 0; i < n_pr; i++) {
        for (int j = 0; j < n_re; j++) {
          int fu = scanf("%d", &alloc[i][j]);
        }
      }
      printf("Max matrix:\n");
      for (int i = 0; i < n_pr; i++) {
        for (int j = 0; j < n_re; j++) {
          int fu = scanf("%d", &max[i][j]);
        }
      }
      printf("Need matrix:\n");
      for (int i = 0; i < n_pr; i++) {
        for (int j = 0; j < n_re; j++) {
          int fu = scanf("%d", &need[i][j]);
        }
      }
      printf("Available matrix:\n");
      for (int i = 0; i < n_re; i++) {
        int fu = scanf("%d", &avail[i]);
      }
      break;

    case 2:
      printf("Printing Data\n");
      printData();
      break;

    case 3:
      printf("Safety Sequence\n");
      safetySequence();
      break;

    case 4:
      printf("Process Request\n");
      processRequest();
      break;

    case 5:
      printf("Exiting the program! Thank you!\n");
      exit(0);
      break;

    default:
      printf("Invalid choice! Please enter a valid choice (1-5).\n");
      break;
    }

    printf("Enter your choice(1-5): ");
    int fu = scanf("%d", &choice);
  }

  return 0;
}
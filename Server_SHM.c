#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = IPC_PRIVATE;
    int shm_id;
    char *shared_memory;

    shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0600);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {

        shared_memory = (char *) shmat(shm_id, NULL, 0);
        if (shared_memory == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        printf("Parent Process:\nEnter a name to convert into uppercase: ");
        if (fgets(shared_memory, SHM_SIZE, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }

        shared_memory[strcspn(shared_memory, "\n")] = '\0';
        if (shmdt(shared_memory) == -1) {
            perror("shmdt");
            exit(1);
        }

        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }

    } else {

      
        shared_memory = (char *) shmat(shm_id, NULL, SHM_RDONLY);
        if (shared_memory == (char *) -1) {
            perror("shmat");
            exit(1);
        }
       wait(NULL);

        char name[SHM_SIZE];
        strcpy(name, shared_memory);

        for (int i = 0; name[i] != '\0'; i++) {
            name[i] = toupper(name[i]);
        }

        printf("Child Process:\nName in Uppercase: %s\n", name);

        if (shmdt(shared_memory) == -1) {
            perror("shmdt");
            exit(1);
        }

        exit(0);
    }

    return 0;
}

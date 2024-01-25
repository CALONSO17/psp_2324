#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int pipeToChild[2];
    int pipeToParent[2];

    if (pipe(pipeToChild) == -1 || pipe(pipeToParent) == -1)
    {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {                           // Child process
        close(pipeToChild[1]);  // Close write end of pipe to child
        close(pipeToParent[0]); // Close read end of pipe to parent

        // Read 3 numbers from parent
        int numbers[3];
        read(pipeToChild[0], numbers, sizeof(numbers));
        close(pipeToChild[0]);

        // Sort the numbers
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2 - i; j++)
            {
                if (numbers[j] > numbers[j + 1])
                {
                    int temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                }
            }
        }

        // Write sorted numbers to parent
        write(pipeToParent[1], numbers, sizeof(numbers));
        close(pipeToParent[1]);

        exit(EXIT_SUCCESS);
    }
    else
    {                           // Parent process
        close(pipeToChild[0]);  // Close read end of pipe to child
        close(pipeToParent[1]); // Close write end of pipe to parent

        // Generate 3 random numbers
        int numbers[3];
        srand(time(NULL));
        for (int i = 0; i < 3; i++)
        {
            numbers[i] = rand() % 100;
            printf("Sending to child: %d\n", numbers[i]);
        }

        // Write numbers to child
        write(pipeToChild[1], numbers, sizeof(numbers));
        close(pipeToChild[1]);

        // Read sorted numbers from child
        read(pipeToParent[0], numbers, sizeof(numbers));
        close(pipeToParent[0]);

        // Display sorted numbers received from child
        printf("Received from child: %d, %d, %d\n", numbers[0], numbers[1], numbers[2]);

        // Wait for child to exit
        wait(NULL);
    }

    return 0;
}

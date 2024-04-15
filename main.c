// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main()
// {
//     pid_t pid1, pid2;
//     int status;

//     printf("Before fork()\n");

//     pid1 = fork();

//     if (pid1 == 0)
//     {
//         printf("Child 1 process\n");
//         // sleep(2); // Child 1 process sleeps for 2 seconds
//         exit(1);  // Child 1 process exits with status 1
//     }
//     else
//     {
//         pid2 = fork();

//         if (pid2 == 0)
//         {
//             printf("Child 2 process\n");
//             // sleep(4); // Child 2 process sleeps for 4 seconds
//             exit(2);  // Child 2 process exits with status 2
//         }
//         else
//         {
//             printf("Parent process\n");

//             // Wait for any child process to terminate and get the status
//             pid_t terminated_pid = waitpid(-1, &status, 0);

//             if (WIFEXITED(status))
//             {
//                 printf("Child process %d terminated with status %d\n", terminated_pid, WEXITSTATUS(status));
//             }

//             // Wait for the other child process to terminate
//             terminated_pid = waitpid(pid1, &status, 0);

//             if (WIFEXITED(status))
//             {
//                 printf("Child process %d terminated with status %d\n", terminated_pid, WEXITSTATUS(status));
//             }
//         }
//     }

//     return 0;
// }


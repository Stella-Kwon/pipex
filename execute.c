#include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
// int main(int argc, char **argv, char **env) 
// {
//     int i;
//     int j;
//         if (argc < 2) {
//         printf("Usage: %s <program> [arguments]\n", argv[0]);
//         return 1;
//     }
//     printf("\n\n\nargv:");
//     i = 0;
//     while(argv[i])
//     {
//         j = 0;
//         while(argv[i][j])
//         {
//             printf("%c", argv[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     printf("\n\n\nenv:");
//     i = 0;
//     while(env[i])
//     {
//         j = 0;
//         while(env[i][j])
//         {
//             printf("%c", env[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     // execve를 사용하여 명령행 인수들을 그대로 실행
//     execve(argv[1], argv + 1, env);

//     // execve가 성공하면 이 부분은 실행되지 않음
//     printf("This line won't be executed\n");

//     return 0;
// }

int main(int argc, char **argv) 
{
    char **env;
    int i;
    int j;

    env = (char **)malloc(sizeof(char *) * 1); // C 언어에서 지역 변수는 자동으로 초기화되지 않으므로, env 포인터가 NULL을 가리키지 않고 임의의 메모리 주소를 참조하고 있습니다. 
    env[0] = NULL;
    if (argc < 2) {
        printf("Usage: %s <program> [arguments]\n", argv[0]);
        return 1;
    }
    printf("\n\n\nargv:");
    i = 0;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            printf("%c", argv[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n\n\nenv:");
    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j])
        {
            printf("%c", env[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    // execve를 사용하여 명령행 인수들을 그대로 실행
   if (execve(argv[1], argv + 1, env) == -1)
            perror("execve error");

    // execve가 성공하면 이 부분은 실행되지 않음
    printf("This line won't be executed\n");

    return 0;
}


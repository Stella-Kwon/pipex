#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *executable_path;

    if (argc > 0)
    {
        // 실행 파일의 경로를 포함한 전체 문자열을 복사
        executable_path = strdup(argv[0]);
        if (executable_path == NULL)
        {
            perror("메모리 할당 오류");
            exit(EXIT_FAILURE);
        }

        // 경로에서 실행 파일의 이름만 추출
        char *file_name = strrchr(executable_path, '/');
        if (file_name != NULL)
        {
            // '/' 이후 문자열이 파일 이름을 포함하므로,
            // 이를 '\0'로 끝내어 파일 이름만 남기고 경로를 제거
            file_name[0] = '\0';
            printf("실행 파일의 경로: %s\n", executable_path);
        }
        else
        {
            printf("실행 파일의 경로를 찾을 수 없습니다.\n");
        }

        // 동적으로 할당된 메모리 해제
        free(executable_path);
    }
    else
    {
        printf("실행 파일의 경로를 찾을 수 없습니다.\n");
    }

    return 0;
}


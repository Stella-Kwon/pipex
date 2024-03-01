#include <stdio.h>

int main(int argc, char **argv, char **env)
{
    // env 배열을 순회하면서 환경 변수 출력
    for (int i = 0; env[i] != NULL; ++i)
    {
        if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
        {
            int j = 0;
            while (env[i][j])
            {
                if (env[i][j] == ':')
                {
                    printf("\n");
                    j++;
                }
                else
                {
                    printf("%c", env[i][j]);
                    j++;
                }
                    
            }
        }
        
    }
    return 0;
}

// it should work like  path + "command"
// command로 받아오는게 /bin/ls이면 path 안붙히고 가는걸로 ~/.dotnet/tools 빼고 path는 /로 시작해서
// 절대 경로는 /로 시작, ~는 현재 사용자의 홈 디렉토리를 나타냅니다. 
// 즉, 절대 경로가 아니라 상대 경로입니다. 사용자의 홈 디렉토리는 /home/사용자명 또는 /Users/사용자명과 같은 형태로 표현
// ~/는 cd => /Users/suminkwon 에 있는 상대경로인 예외이다.  숨겨진파일로 .dotnet폴더에 있다. 살펴보니 도커관련인거같음

#include <stdio.h>

int main() {
    /* 새 파일 생성 */
    int a = 5;
    FILE *fp = fopen("binary", "wb");
    if (fp == NULL) {
        return -1;
    }
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    return 0;
}

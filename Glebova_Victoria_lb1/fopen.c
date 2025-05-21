#include <stdio.h>

int main() {
    char filename[256];
    scanf("%s", filename); 
    if (fopen(filename, "r")) {
        printf("%s: файл %s открыт\n", filename, filename);
    } else {
        printf("%s: ошибка открытия %s\n", filename, filename);
    }
    return 0;
}
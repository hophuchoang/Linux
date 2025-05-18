#include <stdio.h>
#include <stdlib.h>

void gan(char *arr){
    int c = 5;
    *(arr +1) = 10;
}

int main() {

    char arr[5] = {0};

    gan(arr);

    for (int i = 0; i< 5; i++){
        printf("%d\n", arr[i]);
    }


    return 0;
}

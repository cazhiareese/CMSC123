#include <stdio.h>
#include <stdlib.h>

int main (){

    int arr [5] = {0,1,2,3,4};
    int i, x;
    printf("i x: ");
    scanf("%d %d", &i, &x);
    // for (int k = 5; k>i; k--){
    //     arr[k] = arr [k-1];
    // }

    // arr[i] = x;

    // for (int j = i; j<5; j++){
    //     arr[j] = arr[j+1];
    // }
    int counter = 0, found = 0;
    for (int j = 0; j < 5; j++){
        if (x == arr[j]) {
            found = 1;
            break;
        }

        counter++;    
    }

    for(int j=0; j<5;j++){
        printf("%d ", arr[j]);
    }

    printf("\n");
    if (found == 1)
        printf("%d \n", counter);
    else printf("Not found!");

    printf("\n");
    
    return 0;
}
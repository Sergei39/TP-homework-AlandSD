#include <stdio.h>
#include <malloc.h>

void inputArray(float **arr, int row, int col){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float tmp = 0;
            scanf("%f", &tmp);
            arr[i][j] = tmp;
        }
    }
}

void outputArray(float **arr, int row, int col){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float tmp = arr[i][j];
            printf("%f ", tmp);
        }

        printf("\n");
    }
    printf("\n");
}

void swap(float *a, float *b){
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(int *a, int *b){
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void changeArray(float **arr, int row, int col){
    int size = row > col ? row : col;

    for (int i = col; i < row; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size - 1; k++)
                swap(&arr[k][j], &arr[k + 1][j]);

    for (int i = row; i < col; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size - 1; k++)
                swap(&arr[j][k], &arr[j][k + 1]);
}

void trArray(float **arr, int size){
    for (int i = 0; i < size; i++){
        for (int j = size - 1 - i; j >= 0; j--){
            float *a = &arr[i][j];
            float *b = &arr[size - 1 - j][size - 1 - i];
            swap(a, b);
        }
    }
}

int main() {
    int row = 0, col = 0;
    scanf("%d %d", &row, &col);

    float **arr = NULL;
    int size = row > col ? row : col;

    arr = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++){
        arr[i] = (float*)malloc(size * sizeof(float));
    }

    inputArray(arr, row, col);
    printf("Start matrix:\n");
    outputArray(arr, row, col);

    trArray(arr, size);
    changeArray(arr, row, col);
    swap(&row, &col);
    printf("Matrix after change:\n");
    outputArray(arr, row, col);
//

    for (int i = 0; i < size; i++){
        free(arr[i]);
    }

    free(arr);

    return 0;
}
#include <stdio.h>

int add(int a, int b) {
    int result = a + b;
    return result;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;
    printArray(numbers, size);

    int sum = add(10, 20);
    printf("Sum: %d\n", sum);

    int fact = factorial(5);
    printf("Factorial: %d\n", fact);

    return 0;
}

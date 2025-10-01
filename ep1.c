#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    double x = *(double*)a;
    double y = *(double*)b;
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

int main() {
    int n;
    printf("Quantos numeros na serie: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Favor digitar um inteiro positivo.\n");
        return 1;
    }

    double *array = malloc(n * sizeof(double));
    if (array == NULL) { 
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) scanf("%lf", &array[i]);

    qsort(array, n, sizeof(double), compare);

    double min = array[0];
    double max = array[n - 1];

    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += array[i];
    double mean = sum / n;

    double median;
    if (n % 2 == 0) {
        int mid1 = n / 2 - 1;
        int mid2 = n / 2;
        median = (array[mid1] + array[mid2]) / 2.0;
    } else {
        int mid = n / 2;
        median = array[mid];
    }

    double sqSum = 0.0;
    for (int i = 0; i < n; i++) sqSum += pow(array[i] - mean, 2);
    double stdDev = sqrt(sqSum / n);

    printf("Minimum: %.2f\n", min);
    printf("Maximum: %.2f\n", max);
    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Standard deviation: %.15f\n", stdDev);

    free(array);
    return 0;
}

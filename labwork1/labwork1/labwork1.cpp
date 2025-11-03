#include <stdio.h>  
#include <iostream>
#include <cstdlib>

int main() {
    setlocale(LC_ALL, "Ru");
    int N;
    double max, current;
    int scan_result;

    printf("Введите количество чисел N: ");
    scan_result = scanf_s("%d", &N);

    if (scan_result != 1) {
        printf("Ошибка: некорректный ввод количества чисел\n");
        system("pause");
        return 1;
    }

    if (N <= 0) {
        printf("Ошибка: количество чисел должно быть положительным\n");
        system("pause");
        return 1;
    }

    printf("Введите первое число: ");
    scan_result = scanf_s("%lf", &max);

    if (scan_result != 1) {
        printf("Ошибка: некорректный ввод числа\n");
        system("pause");
        return 1;
    }

    for (int i = 1; i < N; i++) {
        printf("Введите следующее число: ");
        scan_result = scanf_s("%lf", &current);

        if (scan_result != 1) {
            printf("Ошибка: некорректный ввод числа\n");
            system("pause");
            return 1;
        }

        if (current > max) {
            max = current;
        }
    }

    printf("Максимальный элемент последовательности: %.2lf\n", max);

    system("pause");
    return 0;
}
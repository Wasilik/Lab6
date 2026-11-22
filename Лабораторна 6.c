#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX 20

int main(void)
{
    int task, rows, cols;

#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    puts("Лабораторна робота №6. Двовимірні масиви");
    puts("1 — №1011: сортування стовпців за характеристиками");
    puts("2 — №908: суми діагоналей вище головної");
    puts("3 — №934: пошук елементів, рівних i + j");
    puts("4 — №978: перестановка блоків хрест-навхрест");
    puts("5 — №929: поділ матриці на два масиви");
    printf("Виберіть завдання: ");
    if (scanf("%d", &task) != 1 || task < 1 || task > 5)
        return 1;

    printf("Введіть кількість рядків і стовпців (1–%d): ", MAX);
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows < 1 || rows > MAX || cols < 1 || cols > MAX)
        return 1;

    if (task == 4 && (rows != cols || rows % 2 != 0)) {
        puts("Потрібна квадратна матриця парного розміру.");
        return 1;
    }

    if (task == 3)
        puts("Рядки та останній стовпець мають строго спадати.");
    puts("Введіть елементи матриці по рядках:");

    if (task == 2 || task == 4) {
        double a[MAX][MAX];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (scanf("%lf", &a[i][j]) != 1)
                    return 1;

        if (task == 2) {
            if (cols == 1)
                puts("Діагоналей вище головної немає.");
            for (int d = 1; d < cols; d++) {
                double sum = 0;
                for (int i = 0; i < rows && i + d < cols; i++)
                    sum += a[i][i + d];
                printf("Діагональ +%d: %g\n", d, sum);
            }
        } else {
            int n = rows / 2;
            double b[MAX][MAX];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    b[i][j] = a[(i + n) % rows][(j + n) % cols];
            puts("Нова матриця:");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    printf(" %10g", b[i][j]);
                puts("");
            }
        }
        return 0;
    }

    int a[MAX][MAX];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (scanf("%d", &a[i][j]) != 1)
                return 1;

    switch (task) {
    case 1: {
        long long sums[MAX] = {0};
        for (int j = 0; j < cols; j++)
            for (int i = 0; i < rows; i++)
                if (a[i][j] < 0 && a[i][j] % 2 != 0)
                    sums[j] -= a[i][j];

        for (int pass = 0; pass < cols - 1; pass++) {
            for (int j = 0; j < cols - 1 - pass; j++) {
                if (sums[j] > sums[j + 1]) {
                    long long sum = sums[j];
                    sums[j] = sums[j + 1];
                    sums[j + 1] = sum;
                    for (int i = 0; i < rows; i++) {
                        int temp = a[i][j];
                        a[i][j] = a[i][j + 1];
                        a[i][j + 1] = temp;
                    }
                }
            }
        }

        puts("Впорядкована матриця:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                printf(" %10d", a[i][j]);
            puts("");
        }
        break;
    }
    case 3: {
        int found = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (a[i][j] == (i + 1) + (j + 1)) {
                    printf("A[%d, %d] = %d\n", i + 1, j + 1, a[i][j]);
                    found = 1;
                }
            }
        }
        if (found == 0)
            puts("Таких елементів немає.");
        break;
    }
    case 5: {
        int nonnegative[MAX * MAX], negative[MAX * MAX];
        int p = 0, q = 0;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (a[i][j] >= 0)
                    nonnegative[p++] = a[i][j];
                else
                    negative[q++] = a[i][j];

        printf("Додатні та нулі:");
        for (int i = 0; i < p; i++)
            printf(" %d", nonnegative[i]);
        printf("\nВід'ємні:");
        for (int i = 0; i < q; i++)
            printf(" %d", negative[i]);
        puts("");
        break;
    }
    }
    return 0;
}

#include <stdio.h>

int max(int arr[], int n) {
    int max_so_far = arr[0],num=0;
    int curr_max = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            num++;
        }
        if (num == n)
        {
            max_so_far = 0;
            return max_so_far;
        }
    }

    for (int i = 1; i < n; i++) {
        curr_max = arr[i] > curr_max + arr[i] ? arr[i] : curr_max + arr[i];
        max_so_far = max_so_far > curr_max ? max_so_far : curr_max;
    }

    return max_so_far;
}

int main() {
    int n, i, num = 0;
    printf("输入n=");
    scanf_s("%d", &n);
    printf("输入序列(用空格隔开):");
    int arr[100] = { 0 };
    for (i = 0; i < n; i++)
    {
        scanf_s("%d", &arr[i]);
    }
    int max_sum = max(arr, n);

    printf("最大子段和为%d\n", max_sum);

    return 0;
}

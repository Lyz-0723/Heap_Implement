#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void swap(int *, int *);

void insert_min_heap(int *, int, int);

void insert_max_heap(int *, int, int);

void insert_min_3_heap(int *, int, int);

void insert_max_3_heap(int *, int, int);

void bottom_up_min_heap(int *, int);

void bottom_up_max_heap(int *, int);

void bottom_up_min_3_heap(int *, int);

void bottom_up_max_3_heap(int *, int);

void delete_min_heap(int *, int);

void delete_max_heap(int *, int);

void delete_max_3_heap(int *, int);

void delete_min_3_heap(int *, int);

void sort_min_heap(int *, int);

void sort_max_heap(int *, int);

void sort_min_3_heap(int *, int);

void sort_max_3_heap(int *, int);

void show_array(int *, int);

void show_binary_heap(int *, int);

void show_3ary_heap(int *, int);

int main() {
    // 初始陣列
    int array[10005] = {16, 5, 8, 10, 12,
                        1, 14, 15, 3, 11,
                        9, 7, 4, 13, 2};
    int len = 15;
    int *heap;

    int type; // 紀錄使用者輸入
    while (1) {
        printf("Array: \n");
        for (int i = 0; i < len; i++)
            printf("%d ", array[i]);

        printf("\n\n");
        printf("Enter your choice\n");
        printf("1. New array\n");
        printf("2. Min Heap\n");
        printf("3. Max Heap\n");
        printf("4. Min 3-ary Heap\n");
        printf("5. Max 3-ary Heap\n");
        printf("6. End\n");

        printf("Enter: ");
        type = getchar() - 48;  // 獲取使用者輸入
        fflush(stdin);

        int is_binary = type == 2 || type == 3 ? 1 : 0; // 判斷使用者選擇為 Binary Heap 還是 3-ary Heap

        if (type == 1) { // 選項1 -> 使用者輸入新陣列
            len = 0;
            int ch, now = 0;
            while ((ch = getchar()) != '\n') { // 重複獲取輸入直到使用者輸入 Enter
                if (ch == ' ') {
                    if (now) {
                        array[len++] = now;
                        now = 0;
                    }
                    continue;
                }
                now = now * 10 + (ch - 48);
            }
            array[len++] = now;
            now = 0;
            printf("\n");
            continue;
        }

        if (type == 6) // 選項6 -> 結束程式
            break;

        printf("\n");
        heap = malloc((len + 1) * sizeof(array[0])); // 根據選項用當前 Array 新增相對應的 Heap (Top Down)
        for (int i = 1; i <= len; i++) {
            if (type == 2)
                insert_min_heap(heap, i, array[i - 1]);    // Min Heap
            else if (type == 3)
                insert_max_heap(heap, i, array[i - 1]);    // Max Heap
            else if (type == 4)
                insert_min_3_heap(heap, i, array[i - 1]);  // Min 3-Heap
            else
                insert_max_3_heap(heap, i, array[i - 1]);  // Max 3-Heap
        }

        while (1) { // 對當前 Heap 選擇不同的操作
            printf("1. Insert\n");
            printf("2. Delete\n");
            printf("3. Toggle\n");
            printf("4. Show\n");
            printf("5. Sort\n");
            printf("6. Back\n");

            printf("Enter: ");
            int choice = getchar() - 48;
            fflush(stdin);
            if (choice == 6) // 選項6 -> 回到上次選擇頁面
                break;

            if (choice == 1) { // 新增新的值到 Heap 中
                int value = 0, ch;
                while ((ch = getchar()) != '\n' && ch != ' ') {  // 獲取使用者輸入
                    value = value * 10 + (ch - 48);
                }

                if (is_binary) { // 根據使用者選擇判斷當前 Heap 的類型並新增值
                    if (type == 2)
                        insert_min_heap(heap, ++len, value);
                    else
                        insert_max_heap(heap, ++len, value);
                    show_array(heap, len);
                    show_binary_heap(heap, len);
                } else {
                    if (type == 4)
                        insert_min_3_heap(heap, ++len, value);
                    else
                        insert_max_3_heap(heap, ++len, value);
                    show_array(heap, len);
                    show_3ary_heap(heap, len);
                }
            }

            if (choice == 2) {   // 對 Heap 做刪除
                if (is_binary) { // 根據使用者選擇判斷當前 Heap 的類型
                    if (type == 2)
                        delete_min_heap(heap, len--);
                    else
                        delete_max_heap(heap, len--);
                    show_array(heap, len);
                    show_binary_heap(heap, len);
                } else {
                    if (type == 4)
                        delete_min_3_heap(heap, len--);
                    else
                        delete_max_3_heap(heap, len--);
                    show_array(heap, len);
                    show_3ary_heap(heap, len);
                }
            }

            if (choice == 3) {   // Toggle (Bottom Up)
                if (is_binary) { // 根據使用者選擇判斷當前 Heap 的類型
                    if (type == 2)
                        bottom_up_max_heap(heap, len);
                    else
                        bottom_up_min_heap(heap, len);
                    type = type == 2 ? 3 : 2;
                    show_array(heap, len);
                    show_binary_heap(heap, len);
                } else {
                    if (type == 4)
                        bottom_up_max_3_heap(heap, len);
                    else
                        bottom_up_min_3_heap(heap, len);
                    type = type == 4 ? 5 : 4;
                    show_array(heap, len);
                    show_3ary_heap(heap, len);
                }
            }

            if (choice == 4) { // 印出 Heap
                show_array(heap, len);
                if (is_binary)
                    show_binary_heap(heap, len);
                else
                    show_3ary_heap(heap, len);
            }

            unsigned long int start = 0, end = 0;
            if (choice == 5) {   // 使用 Heap 做排序
                if (is_binary) { // 根據使用者選擇判斷當前 Heap 的類型
                    if (type == 2) {
                        start = clock();
                        sort_min_heap(heap, len);
                        end = clock();
                    } else {
                        start = clock();
                        sort_max_heap(heap, len);
                        end = clock();
                    }
                    type = type == 2 ? 3 : 2;
                    printf("Sorting spent time: %f\n", (double) (end - start) / CLOCKS_PER_SEC);

                } else {
                    if (type == 4) {
                        start = clock();
                        sort_min_3_heap(heap, len);
                        end = clock();
                    } else {
                        start = clock();
                        sort_max_3_heap(heap, len);
                        end = clock();
                    }
                    type = type == 4 ? 5 : 4;
                    printf("Sorting spent time: %f\n", (double) (end - start) / CLOCKS_PER_SEC);

                }
            }

            printf("\n");
        }
    }
}

void swap(int *a, int *b) { // 交換 a 與 b 的值
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert_min_heap(int *array, int index, int value) { // 新增一值到 Binary Min Heap (TopDown)
    array[index] = value; // 將新增的值放在最後
    while (index != 1 && value < array[index / 2]) {  // 如果新值小於父節點的值
        swap(&array[index], &array[index / 2]); // 交換兩者位置
        index /= 2;                                   // 繼續向上檢查
    }
}

void insert_max_heap(int *array, int index, int value) { // 新增一值到 Binary Max Heap (TopDown)
    array[index] = value; // 將新增的值放在最後
    while (index != 1 && value > array[index / 2]) {  // 如果新值大於父節點的值
        swap(&array[index], &array[index / 2]); // 交換兩者位置
        index /= 2;                                   // 繼續向上檢查
    }
}

void insert_min_3_heap(int *array, int index, int value) { // 新增一值到 3-ary Min Heap (TopDown)
    array[index] = value; // 將新增的值放在最後
    while (index != 1 && value < array[(index + 1) / 3]) {  // 如果新值小於父節點的值
        swap(&array[index], &array[(index + 1) / 3]); // 交換兩者位置
        index = (index + 1) / 3;                            // 繼續向上檢查
    }
}

void insert_max_3_heap(int *array, int index, int value) { // 新增一值到 3-ary Max Heap (TopDown)
    array[index] = value; // 將新增的值放在最後
    while (index != 1 && value > array[(index + 1) / 3]) {  // 如果新值大於父節點的值
        swap(&array[index], &array[(index + 1) / 3]); // 交換兩者位置
        index = (index + 1) / 3;                            // 繼續向上檢查
    }
}

void bottom_up_min_heap(int *array, int index) { // 使用 Bottom Up 的方式製作 Min Heap
    int len = index;

    index /= 2; // 最後一個父節點的 index
    while (index >= 1) {
        int child = index;
        while (1) {  // 判斷當前節點下方子樹是否需要排序
            child = array[child * 2] < array[child * 2 + 1] ? child * 2 : child * 2 + 1;
            if (array[child] > array[child / 2] || child > len)
                break;
            swap(&array[child / 2], &array[child]);
        }
        index--; // 判斷下一個節點
    }
}

void bottom_up_max_heap(int *array, int index) { // 使用 Bottom Up 的方式製作 Max Heap
    int len = index;

    index /= 2; // 最後一個父節點的 index
    while (index >= 1) {
        int child = index;
        while (1) {  // 判斷當前節點下方子樹是否需要排序
            child = array[child * 2] > array[child * 2 + 1] ? child * 2 : child * 2 + 1;
            if (array[child] < array[child / 2] || child > len)
                break;
            swap(&array[child / 2], &array[child]);
        }
        index--; // 判斷下一個節點
    }
}

void bottom_up_min_3_heap(int *array, int index) { // 使用 Bottom Up 的方式製作 Min 3-Heap
    int len = index;

    index = (index + 1) / 2;  // 最後一個父節點的 index
    while (index >= 1) {
        int child = index;
        while (1) {  // 判斷當前節點下方子樹是否需要排序
            if (array[3 * child - 1] < array[3 * child] && array[3 * child - 1] < array[3 * child + 1])
                child = 3 * index - 1;
            else if (array[3 * child] < array[3 * child - 1] && array[3 * child] < array[3 * child + 1])
                child = 3 * child;
            else
                child = 3 * child + 1;

            if (array[child] > array[(child + 1) / 3] || child > len)
                break;
            swap(&array[(int) (child + 1) / 3], &array[child]);
        }
        index--; // 判斷下一個節點
    }
}

void bottom_up_max_3_heap(int *array, int index) { // 使用 Bottom Up 的方式製作 Max 3-Heap
    int len = index;

    index = (index + 1) / 2;  // 最後一個父節點的 index
    while (index >= 1) {
        int child = index;
        while (1) {  // 判斷當前節點下方子樹是否需要排序
            if (array[3 * child - 1] > array[3 * child] && array[3 * child - 1] > array[3 * child + 1])
                child = 3 * index - 1;
            else if (array[3 * child] > array[3 * child - 1] && array[3 * child] > array[3 * child + 1])
                child = 3 * child;
            else
                child = 3 * child + 1;

            if (array[child] < array[(child + 1) / 3] || child > len)
                break;
            swap(&array[(int) (child + 1) / 3], &array[child]);
        }
        index--; // 判斷下一個節點
    }
}

void delete_min_heap(int *array, int index) { // 對 Binary Min Heap 做刪除
    int len = index;
    array[1] = array[index]; // 將 array 最後一位的值替換 root

    index = 1;
    while (1) {
        index = array[2 * index] < array[2 * index + 1] ? 2 * index : 2 * index + 1; // 找出子節點中較小的值
        if (array[index] > array[index / 2] || index > len)                          // 如果子節點比父節點大或沒有子節點了
            break;                                                                   // -> 結束
        swap(&array[index / 2], &array[index]);                                // 將子節點與父節點做交換，並繼續向下檢查
    }
}

void delete_max_heap(int *array, int index) { // 對 Binary Max Heap 做刪除
    int len = index;
    array[1] = array[index]; // 將 array 最後一位的值替換 root

    index = 1;
    while (1) {
        index = array[2 * index] > array[2 * index + 1] ? 2 * index : 2 * index + 1; // 找出子節點中較大的值
        if (array[index] < array[index / 2] || index > len)                          // 如果子節點比父節點小或沒有子節點了
            break;                                                                   // -> 結束
        swap(&array[index / 2], &array[index]);                                // 將子節點與父節點做交換，並繼續向下檢查
    }
}

void delete_min_3_heap(int *array, int index) { // 對 3-ary Min Heap 做刪除
    int len = index;
    array[1] = array[index]; // 將 array 最後一位的值替換 root

    index = 1;
    while (1) {
        // 找出子節點中較小的值
        if (array[3 * index - 1] < array[3 * index] && array[3 * index - 1] < array[3 * index + 1])
            index = 3 * index - 1;
        else if (array[3 * index] < array[3 * index - 1] && array[3 * index] < array[3 * index + 1])
            index = 3 * index;
        else
            index = 3 * index + 1;

        if (array[index] > array[(index + 1) / 3] || index > len)  // 如果子節點比父節點大或沒有子節點了
            break;                                                 // -> 結束
        swap(&array[(int) (index + 1) / 3], &array[index]);  // 將子節點與父節點做交換，並繼續向下檢查
    }
}

void delete_max_3_heap(int *array, int index) { // 對 3-ary Max Heap 做刪除
    int len = index;
    array[1] = array[index]; // 將 array 最後一位的值替換 root

    index = 1;
    while (1) {
        // 找出子節點中較大的值
        if (array[3 * index - 1] > array[3 * index] && array[3 * index - 1] > array[3 * index + 1])
            index = 3 * index - 1;
        else if (array[3 * index] > array[3 * index - 1] && array[3 * index] > array[3 * index + 1])
            index = 3 * index;
        else
            index = 3 * index + 1;

        if (array[index] < array[(index + 1) / 3] || index > len)  // 如果子節點比父節點小或沒有子節點了
            break;                                                 // -> 結束
        swap(&array[(int) (index + 1) / 3], &array[index]);  // 將子節點與父節點做交換，並繼續向下檢查
    }
}

void sort_min_heap(int *array, int size) { // 對 Binary Min Heap 做排序
    int value;

    while (size >= 1) {
        value = array[1];                     // 紀錄 root 的值
        delete_min_heap(array, size);   // 讓 heap 做一次刪除
        array[size--] = value;                // 將 root 值放到 heap 後面
    }
}

void sort_max_heap(int *array, int size) { // 對 Binary Max Heap 做排序
    int value;

    while (size >= 1) {
        value = array[1];                     // 紀錄 root 的值
        delete_max_heap(array, size);   // 讓 heap 做一次刪除
        array[size--] = value;                // 將 root 值放到 heap 後面
    }
}

void sort_min_3_heap(int *array, int size) { // 對 3-ary Min Heap 做排序
    int value;

    while (size >= 1) {
        value = array[1];                     // 紀錄 root 的值
        delete_min_3_heap(array, size); // 讓 heap 做一次刪除
        array[size--] = value;                // 將 root 值放到 heap 後面
    }
}

void sort_max_3_heap(int *array, int size) { // 對 3-ary Max Heap 做排序
    int value;

    while (size >= 1) {
        value = array[1];                     // 紀錄 root 的值
        delete_max_3_heap(array, size); // 讓 heap 做一次刪除
        array[size--] = value;                // 將 root 值放到 heap 後面
    }
}

void show_array(int *array, int size) { // 印出矩陣
    printf("\nArray: \n");
    for (int i = 1; i <= size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void show_binary_heap(int *array, int size) { // 印出 Binary Heap
    int height = (int) (log(size) / log(2)) + 1; // 計算 heap 高度

    printf("\nBinary Heap: \n");

    // 跟據高度印出 Heap
    for (int i = 0; i < height; i++) {
        if (i + 1 != height)
            printf("%*s", (int) pow(2, (height - i)) - 2, " "); // 印出前端的空格
        for (int j = (int) pow(2, i); j < pow(2, i + 1); j++) {
            if (j == size + 1)
                break;
            printf("%02d", array[j]); // 印出 array 中當前 index 的數值
            printf("%*s", (int) pow(2, (height - i + 1)) - 2, " ");  // 印出兩數值之間的間隔
        }
        printf("\n");
    }
    printf("\n");
}

void show_3ary_heap(int *array, int size) { // 印出 3-ary Heap
    int height = ceil(log(2 * size + 1) / log(3)); // 計算 heap高度

    printf("\n3-ary Heap: \n");

    // 跟據高度印出 Heap
    int index = 1;
    for (int i = 0; i < height; i++) {
        if (i + 1 != height)
            printf("%*s", ((int) pow(3, height - i - 1) / 2) * 3, " "); // 印出前端的空格
        for (int j = index; j < index + pow(3, i); j++) {
            if (j == size + 1)
                break;
            printf("%02d", array[j]); // 印出 array 中當前 index 的數值
            if (i + 1 != height)
                printf("%*s", (int) pow(3, (height - i)) - 2, " "); // 印出兩數值之間的間隔
            else
                printf(" ");
        }
        index += (int) pow(3, i);
        printf("\n");
    }
    printf("\n");
}
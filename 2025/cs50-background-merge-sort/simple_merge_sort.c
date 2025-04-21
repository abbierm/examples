#include <stdio.h>

int arry[10] = {1, 4, 81, 16, 63, 12, 44, 8, 23, 87};

void merge_sort(int left, int right);
void print_array(int length);

int main(void) {
    print_array(10);
    merge_sort(0, 9);
    print_array(10);
}

void merge_sort(int left, int right) {
    if (right - left <= 1)
        return;
    int midpoint = (left + right) / 2;
    
    // call merge sort on left side
    merge_sort(left, midpoint);

    // call merge sort on right side
    merge_sort(midpoint + 1, right);

    // make copies of the left and right array
    int l_length = midpoint - left + 1, r_length = right - midpoint;
    int Left[l_length], Right[r_length];

    for (int i = 0; i < midpoint - left + 1; i++)
        Left[i] = arry[left + i];

    for (int j = 0; j < right - midpoint; j++)
        Right[j] = arry[midpoint + 1 + j];

    // cursors for merging two arrays together
    int r = 0, l = 0, cur = left;

    // compares left and right items
    // and 'merges' them into arry
    while (l < l_length && r < r_length) {
        if (Left[l] < Right[r]) {
            arry[cur] = Left[l];
            l++;
        }
        else {
            arry[cur] = Right[r];
            r++;
        }
        cur++;

        if (l == l_length) {
            while (r < r_length) {
                arry[cur] = Right[r];
                r++;
                cur++;
            }
            break;
        }

        if (r == r_length) {
            while (l < l_length) {
                arry[cur] = Left[l];
                l++;
                cur++;
            }
            break;
        }
    }
    return;
}

void print_array(int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        if (i == length - 1)
            printf("%d]\n", arry[i]);
        else
            printf("%d, ", arry[i]);
    }
    return;
}
#include <stdio.h>

int arry[11] = {1, 4, 81, 16, 63, 12, 44, 8, 23, 87};


void merge_sort(int left, int right);
void print_array(int length);

int main(void) {
    print_array(10);
    merge_sort(0, 9);
    print_array(10);
}

void merge_sort(int left, int right) {
    if (left >= right)
        return;
    
    int midpoint = (left + right) / 2;
    
    // call merge sort on left side
    merge_sort(left, midpoint);

    // call merge sort on right side
    merge_sort(midpoint + 1, right);

    // make copies of the left and right array
    int left_length = midpoint - left + 1, right_length = right - midpoint;
    int Left[left_length], Right[right_length];

    for (int i = 0; i < left_length; i++)
        Left[i] = arry[left + i];

    for (int j = 0; j < right_length; j++)
        Right[j] = arry[midpoint + 1 + j];

    // cursors for merging two arrays together
    int r = 0, l = 0, cur = left;

    // compares left and right items
    // and 'merges' them into arry
    while (l < left_length && r < right_length) {
        if (Left[l] < Right[r]) {
            arry[cur] = Left[l];
            l++;
        }
        else {
            arry[cur] = Right[r];
            r++;
        }
        cur++;
        
        // adds remainder of one of the lists when the
        // other list has added all of its values
        if (l == left_length) {
            for (; r < right_length; r++, cur++)
                arry[cur] = Right[r];
            break;
        }
        if (r == right_length) {
            for (; l < left_length; l++, cur++)
                arry[cur] = Left[l];
            break;
        }
    }
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

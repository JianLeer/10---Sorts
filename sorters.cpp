#include <iostream>
#include <vector>
using namespace std;

//#1 冒泡排序 - 交换类
void bubbleSort(vector<int>& data) {
    int n = data.size();
    bool loop = true; // 减少无效loop
    for (int i = 0; i < n - 1 && loop; i++) {
        for (int j = n - 1, loop = false; j > i; j--) {
            if (data[j] < data[j - 1]) {
                swap(data[j], data[j - 1]);
                loop = true;
            }
        }
    }
}

//#2 快速排序 - 交换类；pivot的选择导致**排序的不稳定**
void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int pivot = nums[left];
    int c1 = left, c2 = right;
    while (c1 < c2) {
        while (c1 < c2 && nums[c2] > pivot) c2--; // 不满足后大的元素
        if (c1 < c2) nums[c1++] = nums[c2]; // 交换
        while (c1 < c2 && nums[c1] <= pivot) c1++; // 不满足前小的元素
        if (c1 < c2) nums[c2--] = nums[c1]; // 交换
    }
    nums[c1] = pivot;
    quickSort(nums, left, c1 - 1);
    quickSort(nums, c1 + 1, right);
}

//#3 选择排序 - 选择类；**不稳定排序**
void selectionSort(vector<int>& data) {
    int n = data.size();
    for (int i = 0, j, min; i < n - 1; i++) {
        for (j = i + 1, min = i; j < n; j++) {
            if (data[min] > data[j]) min = j;
        }
        swap(data[min], data[i]);
    }
}

//#4 堆排序 - 选择类；**不稳定排序**
{
    void heapSort(vector<int>& nums) {
        int n = nums.size();
        for (int i = nums.size()/2 - 1; i >= 0; --i) {
            heapBuild(nums, i, nums.size());
        }
        for (int i = nums.size() - 1; i > 0; i--) {
            swap(nums[0], nums[i]);
            heapBuild(nums, 0, i);
        }
    }
    void heapBuild(vector<int>& nums, int root, int end) {
        int left = 2 * root + 1;
        if (left >= end) return;
        int right = left + 1;
        int minIdx = ((right < end) && (nums[right] < nums[left]))?right:left;
        if (nums[minIdx] < nums[root]) {
            swap(nums[root], nums[minIdx]);
            heapBuild(nums, minIdx, end);
        } 
    }
}

//#5 插入排序 - 插入类
void insertSort(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return;
    for (int i = 1; i < nums.size(); i++) {
        for (int j = i - 1; j >= 0 && nums[j] > nums[j+1]; j--)
            swap(nums[j], nums[j+1]);
    }
}

//#6 希尔排序 - 插入类；**不稳定排序** gap的问题
void insertSort(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < nums.size(); i++) {
            for (int j = i - gap; j >= 0 && nums[j] > nums[j+gap]; j-=gap)
                swap(nums[j], nums[j + gap]);
        }
    }
}

//#7 归并排序 - 归并
{
    void merge(vector<int>& nums, int a, int b , int c) {
        vector<int> nums2 {nums.begin()+b+1, nums.begin()+c+1};
        int x = b, y = nums2.size() - 1, z = c;
        while (x >= a && y >= 0) {
            if (nums[x] > nums2[y]) nums[z--] = nums[x--];
            else nums[z--] = nums2[y--];
        }
        while (y >= 0) nums[z--] = nums2[y--];
    }
    void mergeSort(vector<int>& nums, int left, int right) { // 递归法
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
    void mergeSort(vector<int>& nums) { // 迭代法
        int sz = 1, left, mid, right;
        int N = nums.size();
        while (sz < N) {
            left = 0; // 先sz = 1排一波 sz = 2 排一波 ...
            while (left + sz < N) {
                mid = left + sz - 1;
                right = mid + sz;
                if (right >= N) right = N - 1;
                merge(nums, left, mid, right);
                left = right + 1;
            }
            sz *= 2;
        }
    }
}

//分配类排序：计数排序+桶排序+基数排序
// TODO

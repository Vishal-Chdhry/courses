#include <iostream>
using namespace std;

void merge(int array[], int const left, int const mid, int const right,
           int *inv) {
  auto const subArrayOne = mid - left + 1;
  auto const subArrayTwo = right - mid;

  auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

  for (auto i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

  auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
  int indexOfMergedArray = left;

  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    } else {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
      *inv += subArrayOne - indexOfSubArrayOne;
    }
    indexOfMergedArray++;
  }
  while (indexOfSubArrayOne < subArrayOne) {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  while (indexOfSubArrayTwo < subArrayTwo) {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
  delete[] leftArray;
  delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end, int *inv) {
  if (begin >= end) return;

  auto mid = begin + (end - begin) / 2;
  mergeSort(array, begin, mid, inv);
  mergeSort(array, mid + 1, end, inv);
  merge(array, begin, mid, end, inv);
}

void printArray(int A[], int size) {
  for (auto i = 0; i < size; i++) cout << A[i] << " ";
}

int main() {
  int arr[] = {12,  11, 13, 5,   6,     7,   21,  31,  23, 123,
               1,   2,  3,  12,  312,   3,   12,  3,   12, 3,
               123, 12, 4,  125, 23415, 345, 123, 412, 34, 12341};
  auto arr_size = sizeof(arr) / sizeof(arr[0]);

  int inversions = 0;
  cout << "Given array is \n";
  printArray(arr, arr_size);

  mergeSort(arr, 0, arr_size - 1, &inversions);

  cout << "\nSorted array is \n";
  printArray(arr, arr_size);

  cout << "INVERSIONS: " << inversions << endl;
  return 0;
}

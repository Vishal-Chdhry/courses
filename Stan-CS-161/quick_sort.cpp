#include <bits/stdc++.h>
using namespace std;

int
partition (int arr[], int low, int high, int *inversions)
{
 int mid = (high + low) / 2;
 int median = low;

  if (arr[low] < arr[high]) {
    if (arr[low] > arr[mid]) {
     median = low;
    } else if (arr[high] < arr[mid]) {
     median = high;
    } else {
     median = mid;
    }
  } else {
    if (arr[low] < arr[mid]) {
     median = low;
    } else if (arr[high] > arr[mid]) {
     median = high;
    } else {
     median = mid;
    }
  }

 swap (arr[low], arr[median]);
 int partition = low;
 cout << median << endl;

  for (int ix = low + 1; ix <= high; ix++) {
   *inversions = *inversions + 1;
    if (arr[ix] < arr[low]) {
     swap (arr[ix], arr[++partition]);
   }
  }
 swap (arr[low], arr[partition]);
 return partition;
}

void
quickSort (int arr[], int low, int high, int *inversions)
{
  if (low < high) {
   int pos = partition (arr, low, high, inversions);
   cout << pos << endl;

   quickSort (arr, low, pos - 1, inversions);
   quickSort (arr, pos + 1, high, inversions);
 }
}

int
main ()
{
 int n;
 cout << " enter the size of array";
 cin >> n;
 int inv = 0;
 int arr[n];
  for (int i = 0; i < n; i++) {
   cin >> arr[i];
  }
 quickSort (arr, 0, n - 1, &inv);
 cout << "The sorted array is: ";
  for (int i = 0; i < n; i++) {
   cout << arr[i] << "\t";
  }

 cout << endl << "INV: " << inv;
}
#include <bits/stdc++.h>
using namespace std;

// Function to find the sum of larger
// numbers represented as a string
string findSum(string str1, string str2) {
  if (str1.length() > str2.length()) swap(str1, str2);

  string str = "";

  int n1 = str1.length();
  int n2 = str2.length();

  reverse(str1.begin(), str1.end());
  reverse(str2.begin(), str2.end());

  int carry = 0;
  for (int i = 0; i < n1; i++) {
    int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
    str.push_back(sum % 10 + '0');

    carry = sum / 10;
  }

  for (int i = n1; i < n2; i++) {
    int sum = ((str2[i] - '0') + carry);
    str.push_back(sum % 10 + '0');
    carry = sum / 10;
  }

  if (carry) str.push_back(carry + '0');

  reverse(str.begin(), str.end());

  return str;
}

// Function to find difference of larger
// numbers represented as strings
string findDiff(string str1, string str2) {
  string str = "";

  int n1 = str1.length(), n2 = str2.length();

  reverse(str1.begin(), str1.end());
  reverse(str2.begin(), str2.end());

  int carry = 0;

  for (int i = 0; i < n2; i++) {
    int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

    if (sub < 0) {
      sub = sub + 10;
      carry = 1;
    } else
      carry = 0;

    str.push_back(sub + '0');
  }

  for (int i = n2; i < n1; i++) {
    int sub = ((str1[i] - '0') - carry);

    if (sub < 0) {
      sub = sub + 10;
      carry = 1;
    } else
      carry = 0;

    str.push_back(sub + '0');
  }

  reverse(str.begin(), str.end());

  return str;
}

// Function to remove all leading 0s
// from a given string
string removeLeadingZeros(string str) {
  const regex pattern("^0+(?!$)");
  str = regex_replace(str, pattern, "");
  return str;
}

// Function to multiply two numbers
// using Karatsuba algorithm
string multiply(string A, string B) {
  if (A.length() > B.size()) {
    swap(A, B);
  }

  while (A.length() != B.size()) {
    A = '0' + A;
  }

  if (A.size() == 1) {
    return to_string(stoi(A) * stoi(B));
  } else {
    if (A.size() % 2) {
      A = '0' + A;
      B = '0' + B;
    }
    string AL = "", AR = "", BL = "", BR = "";

    for (int i = 0; i < A.size() / 2; i++) {
      AL += A[i];
      BL += B[i];
    }

    for (int i = A.size() / 2; i < A.size(); i++) {
      AR += A[i];
      BR += B[i];
    }

    string ac = multiply(AL, BL);
    string bd = multiply(AR, BR);

    string mid =
        findDiff(multiply(findSum(AL, AR), findSum(BL, BR)), findSum(ac, bd));
    for (int i = 0; i < A.size() / 2; i++) {
      mid += '0';
    }

    for (int i = 0; i < A.size(); i++) {
      ac += '0';
    }
    string ans = findSum(ac, findSum(mid, bd));

    return removeLeadingZeros(ans);
  }
}

int main() {
  string A = "74638463789";
  string B = "35284567382";
  cout << multiply(A, B);
  return 0;
}

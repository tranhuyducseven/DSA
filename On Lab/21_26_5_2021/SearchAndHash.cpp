#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;

int binarySearch(int arr[], int left, int right, int x)
{
    if (right >= left) 
    {
        int index = left + (right - left) / 2;
        cout << "We traverse on index: " << index << endl;
        if (arr[index] == x)
            return index;
        if (arr[index] > x)
            return binarySearch(arr, left, index - 1, x);
        return binarySearch(arr, index + 1, right, x);
    }
    return -1;
}

int jumpSearch(int arr[], int x, int n)
{
    int jump = (int)sqrt(n);
    int jIndex = 0;
    while (arr[jIndex] <= x && jIndex < n)
    {
        cout << jIndex << " ";
        if (arr[jIndex] == x) 
            return jIndex;
        jIndex += jump;
    }
    if (jIndex < n)
        cout << jIndex << " ";
    jIndex -= jump;
    for (int i = 1; i < jump; i++) 
    {
        cout << jIndex + i << " ";
        if (arr[jIndex + i] == x) 
            return jIndex + i;
    }
    return -1;
}


int interpolationSearch(int arr[], int left, int right, int x)
{
    int index;
    if (left <= right && x >= arr[left] && x <= arr[right]) 
    {
        index = left + (((double)(right - left) / (arr[right] - arr[left])) * (x - arr[left]));
        cout << "We traverse on index: " << index << endl;
        if (arr[index] == x)
            return index;
        if (arr[index] < x)
            return interpolationSearch(arr, index + 1, right, x);
        if (arr[index] > x)
            return interpolationSearch(arr, left, index - 1, x);
    }
    return -1;
}
    
int foldShift(long long key, int addressSize)
{
    long long divider = 1;
    while ((key / divider) > 9)
        divider *= 10;
    long long power = (long long)pow(10, addressSize - 1);
    int result = 0;
    int fold = 0;
    while (divider != 0)
    {
        int value = (int)(key / divider);
        key = key - divider * value;
        divider /= 10;
        if (power <= 0)
        {
            result += fold;
            fold = 0;
            power = (int)pow(10, addressSize - 1);
        }
        fold += (int)(value * power);
        power /= 10;
    }
    if (power != 0)
        fold = (int)(fold / (power * 10));
    result = result + fold;
    power = (int)pow(10, addressSize);
    result %= power;
    return result;
}

int rotation(long long key, int addressSize)
{
    long long divider = 1;
    while ((key / divider) > 9)
        divider *= 10;
    int lo = key % 10;
    key = key / 10 + lo * divider;
    return foldShift(key, addressSize);
}

long int midSquare(long int seed)
{
    long long int temp = seed * seed;
    temp = temp / 100;
    long int result = 0;
    long int mul = 1;
    int loop = 0;
    while (temp != 0 && loop < 4)
    {
        int value = (int)((temp % 10) * mul);
        mul *= 10;
        temp /= 10;
        result += value;
        loop++;
    }
    return result;
}

long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}

long int digitExtraction(long int seed, int* extractDigits, int size)
{
    long int division = 1;
    int n = 1;
    while (seed / division > 9)
    {
        division *= 10;
        n++;
    }
    int* arr = new int[n];
    for (int i = n-1; i >= 0; i--)
    {
        int value = (int)(seed % 10);
        arr[i] = value;
        seed /= 10;
    }
    long int result = 0;
    for (int i = 0; i < size; i++)
		result = result + arr[extractDigits[i]] * (long int)pow(10, size - 1 - i);
	delete[] arr;
	return result;
}


bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise
    map <int, pair <int, int>> listSum;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
            if (listSum.find(sum) == listSum.end())
                listSum[sum] = make_pair(arr[i], arr[j]);
            else
            {
                pair1 = listSum[sum];
                pair2 = make_pair(arr[i], arr[j]);
                return true;
            }
        }
    }
    return false;
}
bool checkAnswer(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
    int cntHave = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == pair1.first || arr[i] == pair1.second || arr[i] == pair2.first || arr[i] == pair2.second)
            cntHave++;
    }
    if (cntHave != 4)
        return false;
    return (pair1.first + pair1.second == pair2.first + pair2.second);
}

void solveQ1()
{
    cout << "-------------------------Question 1---------------------------" << endl;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array": cout << "Element is present at index " << result;
    cout << endl << "--------------------------------------------------------------" << endl << endl;
}

void solveQ21()
{
    cout << "-------------------------Question 2.1-------------------------" << endl;
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);
    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ22()
{
    cout << "-------------------------Question 2.2-------------------------" << endl;
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 144;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);
    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ31()
{
    cout << "-------------------------Question 3.1-------------------------" << endl;
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
    : cout << "Element is present at index " << result;
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ32()
{
    cout << "-------------------------Question 3.2-------------------------" << endl;
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 0;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
    : cout << "Element is present at index " << result;
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ4()
{
    cout << "-------------------------Question 4-------------------------" << endl;
    cout << rotation(600101, 2);
    cout << endl << "------------------------------------------------------------" << endl << endl;
}

void solveQ51()
{
    cout << "-------------------------Question 5.1-------------------------" << endl;
    int a[]={1,2,5};
    cout << digitExtraction(122443, a, 3);
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ52()
{
    cout << "-------------------------Question 5.2-------------------------" << endl;
    cout << midSquare(9452);
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ61()
{
    cout << "-------------------------Question 6.1-------------------------" << endl;
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) 
    {
        if (checkAnswer(arr, n, pair1, pair2))
            printf("Your answer is correct.\n");
        else 
            printf("Your answer is incorrect.\n");
    }
    else 
        printf("No pair found.\n");
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

void solveQ62()
{
    cout << "-------------------------Question 6.2-------------------------" << endl;
    int arr[] = { 3, 4, 7 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) 
    {
        if (checkAnswer(arr, n, pair1, pair2))
            printf("Your answer is correct.\n");
        else 
            printf("Your answer is incorrect.\n");
    }
    else 
        printf("No pair found.\n");
    cout << endl << "---------------------------------------------------------------" << endl << endl;
}

int main()
{
    solveQ1();
    solveQ21();
    solveQ22();
    solveQ31();
    solveQ32();
    solveQ4();
    solveQ51();
    solveQ52();
    solveQ61();
    solveQ62();
}

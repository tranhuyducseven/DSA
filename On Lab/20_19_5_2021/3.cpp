#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    //Helping functions go here
    void reheapDown(int maxHeap[], int numberOfElements, int index)
    {
        int leftChild = 2 * index + 1;
        if (leftChild <= numberOfElements - 1)
        {
            int rightChild = leftChild + 1;
            int child = leftChild;
            if (rightChild <= numberOfElements - 1 && maxHeap[rightChild] > maxHeap[leftChild])
                child = rightChild;
            if (maxHeap[index] < maxHeap[child])
            {
                swap(maxHeap[index], maxHeap[child]);
                reheapDown(maxHeap, numberOfElements, child);
            }
        }
    }
    static void heapSort(T *start, T *end)
    {
        //TODO

        Sorting<T>::printArray(start, end);
    }
};
#endif /* SORTING_H */
int main()
{
    int arr[4] = {4, 2, 9, 1};
    Sorting<int>::heapSort(&arr[0], &arr[4]);
    return 0;
}
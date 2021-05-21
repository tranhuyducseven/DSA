#include <iostream>
using namespace std;
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

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (index >= numberOfElements || index == 0)
        return;
    int parent = (index - 1) / 2;
    if (maxHeap[parent] < maxHeap[index])
    {
        swap(maxHeap[index], maxHeap[parent]);
        reheapUp(maxHeap, numberOfElements, parent);
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    reheapDown(arr, size, 0);
    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "]";
    return 0;
}